#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"
using namespace std;
#endif /* __PROGTEST__ */

//version control
//#include <iostream> //TODO smazat
pthread_mutex_t g_Switch;
pthread_t threads[65];
bool threadsUsed[65];
pthread_attr_t   attr;
struct arg_struct {
    CCPU * ccpu;
    void * arg2;
    void (* entryPoint) ( CCPU *, void * );
};


class CWhateverNiceNameYouLike : public CCPU
{
  public:

    virtual uint32_t         GetMemLimit                   ( void ) const;
    virtual bool             SetMemLimit                   ( uint32_t          pages );
    virtual bool             NewProcess                    ( void            * processArg,
                                                             void           (* entryPoint) ( CCPU *, void * ),
                                                             bool              copyMem );

    using CCPU::CCPU;
    void Resize(void * mem, uint32_t totalPages);
    void FreeMemory(uint32_t totalPages);
    uint32_t pages;
    uint32_t * tmp;
    uint32_t beginLevel1;
  protected:

    bool HardCopy(CWhateverNiceNameYouLike * prevCCPU, CWhateverNiceNameYouLike * newCCPU);
    uint32_t HowManyPagesLeft(){
        return (tmp[1] - tmp[0] + 1) + pages;
    };
    uint32_t nOfRows(uint32_t totalPages);
   /*
    if copy-on-write is implemented:

    virtual bool             pageFaultHandler              ( uint32_t          address,
                                                             bool              write );
    */
};



void               MemMgr                                  ( void            * mem, // zasobnik
                                                             uint32_t          totalPages,
                                                             void            * processArg,
                                                             void           (* mainProcess) ( CCPU *, void * ))
{
    pthread_mutex_init ( &g_Switch, NULL );
    pthread_attr_init ( &attr );
    pthread_attr_setdetachstate ( &attr, PTHREAD_CREATE_JOINABLE );
    pthread_mutex_lock(&g_Switch);

    uint32_t *tmp = (uint32_t *)mem;
    tmp[0] = 0;
    tmp[1] = totalPages;

    //INICIALIZACE THREADS
    for(int i=0;i<65;i++){
        threadsUsed[i] = false;
    }
    //END INICIALIZACE THREADS

    //GET PAGES BEGINNING
    uint32_t pages = (tmp[1])/CCPU::PAGE_DIR_ENTRIES;
    uint32_t myRemain = (tmp[1])%CCPU::PAGE_DIR_ENTRIES;
    pages = (myRemain > 0 ) ? (pages+1) : pages;
    //END GET PAGES BEGINNING

    //ZERO LEVEL1
    for(uint32_t i = pages;i<PROCESS_MAX+pages;i++){
        tmp[i*CCPU::PAGE_DIR_ENTRIES] = 0;
    }
    //END ZERO LEVEL 1
    //FILL STACK
    tmp[0] = pages+PROCESS_MAX;
    for(uint32_t i = tmp[0];i<tmp[1];i++){
        tmp[i] = i;
    }
    // END FILL STACK

    // GET STARTLEVEL1
    uint32_t startLevel1 = -1;
    for(uint32_t i = pages;i<PROCESS_MAX+pages;i++){
        if(tmp[i*CCPU::PAGE_DIR_ENTRIES] == 0){
            startLevel1 = i;
            tmp[i*CCPU::PAGE_DIR_ENTRIES] = 1;
            break;
        }
    }
    //END GETSTARTLEVEL1


    CWhateverNiceNameYouLike * myCCPU = new CWhateverNiceNameYouLike((uint8_t *) mem,startLevel1*CCPU::PAGE_SIZE);
    myCCPU->tmp = (uint32_t *)mem;
    myCCPU->pages = 0;
    myCCPU->beginLevel1 = pages;


    pthread_mutex_unlock(&g_Switch);
    mainProcess(myCCPU,processArg);

    void* ret = NULL;
    for(int i=0;i<65;i++){
        if(threadsUsed[i] != false) {
            pthread_join(threads[i],&ret);
        }
    }

    delete myCCPU;
}

uint32_t CWhateverNiceNameYouLike::nOfRows(uint32_t totalPages){
    uint32_t level1 = totalPages/CCPU::PAGE_DIR_ENTRIES;
    uint32_t myRemain = totalPages%CCPU::PAGE_DIR_ENTRIES;
    level1 = (myRemain > 0 ) ? (level1+1) : level1;
    return level1;
}

void CWhateverNiceNameYouLike::FreeMemory(uint32_t totalPages) {
    if( totalPages < this->pages){
        uint32_t level1Before = this->nOfRows(this->pages);
        uint32_t level1Now = this->nOfRows(totalPages);
        uint32_t level2RemainBefore = (this->pages%CCPU::PAGE_DIR_ENTRIES==0 && this->pages != 0) ? CCPU::PAGE_DIR_ENTRIES : this->pages%CCPU::PAGE_DIR_ENTRIES;

        for(uint32_t i=level1Now;i<level1Before;i++){
            uint32_t maximum;
            if( (i+1) == level1Before){
                maximum = level2RemainBefore;
            }
            else {
                maximum = CCPU::PAGE_DIR_ENTRIES;
            }
            for (uint32_t j = 0; j < maximum; j++) {
                tmp[0] -= 1;
                uint32_t temporary = tmp[this->m_PageTableRoot/4 + i] >> 12; //level 1 schranka
                tmp[tmp[0]] = tmp[temporary*CCPU::PAGE_DIR_ENTRIES + j] >> 12;
                tmp[temporary*CCPU::PAGE_DIR_ENTRIES + j] = 0;
            }
            tmp[0] -= 1;
            tmp[tmp[0]] = tmp[this->m_PageTableRoot/4 + i] >> 12;
            tmp[this->m_PageTableRoot/4 + i] = 0;
        }
        //level2
        if(totalPages != 0) {
            if (level1Before > level1Now) {
                level2RemainBefore = CCPU::PAGE_DIR_ENTRIES;
            }
            uint32_t level2RemainNow = (totalPages % CCPU::PAGE_DIR_ENTRIES == 0 && totalPages != 0)
                                       ? CCPU::PAGE_DIR_ENTRIES : totalPages % CCPU::PAGE_DIR_ENTRIES;
            for (uint32_t j = level2RemainNow; j < level2RemainBefore; j++) {
                tmp[0] -= 1;
                uint32_t temporary =
                        tmp[this->m_PageTableRoot/4 + (level1Now - 1)] >> 12; //level 1 schranka
                tmp[tmp[0]] = tmp[temporary * CCPU::PAGE_DIR_ENTRIES + j] >> 12;
                tmp[temporary * CCPU::PAGE_DIR_ENTRIES + j] = 0;
            }
            if (level2RemainNow == 0) {
                tmp[0] -= 1;
                tmp[tmp[0]] = tmp[this->m_PageTableRoot/4 + (level1Now - 1)] >> 12;
                tmp[this->m_PageTableRoot/4 + (level1Now - 1)] = 0;
            }
        }
    }
}


void CWhateverNiceNameYouLike::Resize(void *mem, uint32_t totalPages) {
    this->FreeMemory(totalPages);
    if(totalPages > this->pages) {
        uint32_t level1Before = this->nOfRows(this->pages);
        uint32_t level1Now = this->nOfRows(totalPages);
        if(level1Now > level1Before){
            uint32_t level2RemainBefore = (this->pages%CCPU::PAGE_DIR_ENTRIES==0 && this->pages != 0) ? CCPU::PAGE_DIR_ENTRIES : this->pages%CCPU::PAGE_DIR_ENTRIES;
            uint32_t level2RemainNow = (totalPages%CCPU::PAGE_DIR_ENTRIES==0 && totalPages != 0) ? CCPU::PAGE_DIR_ENTRIES : totalPages%CCPU::PAGE_DIR_ENTRIES;
            if(level1Before != 0) {
                for (uint32_t j = level2RemainBefore; j < CCPU::PAGE_DIR_ENTRIES; j++) {
                    uint32_t temporary = tmp[this->m_PageTableRoot/4 + (level1Before - 1)]>> 12; //level1 stranka
                    tmp[temporary*CCPU::PAGE_DIR_ENTRIES +j] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
                    tmp[0] += 1;
                }
            }
            for(uint32_t i = level1Before; i < level1Now-1 ; i++) {
                tmp[this->m_PageTableRoot/4+i] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
                tmp[0] += 1;
                for (uint32_t j = 0; j < CCPU::PAGE_DIR_ENTRIES; j++) {
                    uint32_t temporary = tmp[this->m_PageTableRoot/4 + i] >> 12; //level1 stranka
                    tmp[temporary*CCPU::PAGE_DIR_ENTRIES+j] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
                    tmp[0] += 1;
                }
            }
            tmp[this->m_PageTableRoot/4+(level1Now - 1)] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
            tmp[0] += 1;
            for(uint32_t j = 0; j< level2RemainNow; j++){
                uint32_t temporary = tmp[this->m_PageTableRoot/4+(level1Now - 1)]>> 12; //level1 stranka
                tmp[temporary*CCPU::PAGE_DIR_ENTRIES +j] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
                tmp[0] += 1;
            }
        }
        else{
            uint32_t level2RemainBefore = (this->pages%CCPU::PAGE_DIR_ENTRIES==0 && this->pages != 0) ? CCPU::PAGE_DIR_ENTRIES : this->pages%CCPU::PAGE_DIR_ENTRIES;
            uint32_t level2RemainNow = (totalPages%CCPU::PAGE_DIR_ENTRIES==0 && totalPages != 0) ? CCPU::PAGE_DIR_ENTRIES : totalPages%CCPU::PAGE_DIR_ENTRIES;
            for(uint32_t j = level2RemainBefore; j< level2RemainNow; j++){
                uint32_t temporary = tmp[this->m_PageTableRoot/4+(level1Before - 1)] >> 12; //level1 stranka
                tmp[temporary*CCPU::PAGE_DIR_ENTRIES +j] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
                tmp[0] += 1;
            }
        }
        //tmp[i] = ((i + 1) << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
    }
}

uint32_t  CWhateverNiceNameYouLike::GetMemLimit ( void ) const{
    return this->pages;
}

bool CWhateverNiceNameYouLike::SetMemLimit(uint32_t pages){
    pthread_mutex_lock(&g_Switch);
    if(pages > this->HowManyPagesLeft()){
        return false;
    }
    this->Resize(this->tmp,pages);
    this->pages = pages;
    pthread_mutex_unlock(&g_Switch);
    return true;
}

void *meziFunkce (void *myStruct) {
    struct arg_struct *cteniParametru = (struct arg_struct *)myStruct;
    cteniParametru->entryPoint(cteniParametru->ccpu,cteniParametru->arg2);
    delete cteniParametru->ccpu;
    delete cteniParametru;
    return NULL;
}

bool CWhateverNiceNameYouLike::HardCopy(CWhateverNiceNameYouLike * prevCCPU, CWhateverNiceNameYouLike * newCCPU){
    if(this->HowManyPagesLeft() < prevCCPU->pages){
        return false;
    }
    newCCPU->pages = prevCCPU->pages;
    uint32_t nOfRowsLevel1 = this->nOfRows(prevCCPU->pages);
    for(uint32_t i = 0;i<nOfRowsLevel1;i++){
        tmp[newCCPU->m_PageTableRoot/4 + i] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
        tmp[0] += 1;
        uint32_t maximum;
        if(i+1 != nOfRowsLevel1){
            maximum = CCPU::PAGE_DIR_ENTRIES;
        }
        else{
            maximum = prevCCPU->pages%CCPU::PAGE_DIR_ENTRIES;
        }
        for(uint32_t j = 0; j < maximum; j++){
            uint32_t temporary = (tmp[newCCPU->m_PageTableRoot/4 + i] >> 12) * CCPU::PAGE_DIR_ENTRIES + j;
            tmp[temporary] = (tmp[tmp[0]] << 12) | CCPU::BIT_WRITE | CCPU::BIT_USER | CCPU::BIT_PRESENT;
            tmp[0] += 1;
            for(uint32_t k = 0; k < CCPU::PAGE_DIR_ENTRIES;k++){
                uint32_t temporaryLevel3 = (tmp[temporary] >> 12) * CCPU::PAGE_DIR_ENTRIES + k;
                uint32_t prevLevel2 = (tmp[prevCCPU->m_PageTableRoot/4 + i] >> 12) * CCPU::PAGE_DIR_ENTRIES + j;
                uint32_t prevLevel3 = (tmp[prevLevel2] >> 12) * CCPU::PAGE_DIR_ENTRIES + k;
                tmp[temporaryLevel3] = tmp[prevLevel3];
            }
        }
    }
    return true;
}

bool CWhateverNiceNameYouLike::NewProcess( void * processArg, void (* entryPoint) ( CCPU *, void * ), bool copyMem ){
    pthread_mutex_lock(&g_Switch);

    // GET STARTLEVEL1
    uint32_t startLevel1 = -1;
    for(uint32_t i = beginLevel1;i<PROCESS_MAX+beginLevel1;i++){
        if(this->tmp[i*CCPU::PAGE_DIR_ENTRIES] == 0){
            startLevel1 = i;
            this->tmp[i*CCPU::PAGE_DIR_ENTRIES] = 1;
            break;
        }
    }
    //END GETSTARTLEVEL1


    CWhateverNiceNameYouLike * myCCPU = new CWhateverNiceNameYouLike((uint8_t *) this->tmp,startLevel1*CCPU::PAGE_SIZE);
    myCCPU->tmp = (uint32_t *)this->tmp;
    myCCPU->pages = 0;
    myCCPU->beginLevel1 = this->beginLevel1;
    if(copyMem){
        if (!HardCopy(this,myCCPU)){
            return false;
        }
    }


    struct arg_struct * myStruct = new arg_struct();
    myStruct->ccpu = myCCPU;
    myStruct->arg2 = processArg;
    myStruct->entryPoint = entryPoint;

    threadsUsed[startLevel1-beginLevel1] = true;


//    thread * t = new thread(entryPoint,myCCPU,processArg);
    pthread_create(&threads[startLevel1-beginLevel1],&attr,meziFunkce,myStruct); //TODO
    pthread_mutex_unlock(&g_Switch);
//    entryPoint(myCCPU,processArg);
    return true;
}