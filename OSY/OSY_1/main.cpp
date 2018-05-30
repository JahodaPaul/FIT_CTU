#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <pthread.h>
#include <semaphore.h>
#include <cstdint>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>
using namespace std;


class CFITCoin;
class CCVUTCoin;
class CCustomer;

typedef struct shared_ptr<CFITCoin>                        AFITCoin;
typedef struct shared_ptr<CCVUTCoin>                       ACVUTCoin;
typedef struct shared_ptr<CCustomer>                       ACustomer;
//=================================================================================================
class CFITCoin
{
public:
    CFITCoin                      ( const vector<uint32_t> & vectors,
                                    int               distMax )
            : m_Vectors ( vectors ),
              m_DistMax ( distMax ),
              m_Count ( 0 )
    {
    }
    virtual                  ~CFITCoin                     ( void ) = default;
    vector<uint32_t>         m_Vectors;
    int                      m_DistMax;
    uint64_t                 m_Count;
};
//=================================================================================================
class CCVUTCoin
{
public:
    CCVUTCoin                     ( const vector<uint8_t> & data,
                                    int               distMin,
                                    int               distMax )
            : m_Data ( data ),
              m_DistMin ( distMin ),
              m_DistMax ( distMax ),
              m_Count ( 0 )
    {
    }
    virtual                  ~CCVUTCoin                    ( void ) = default;
    vector<uint8_t>          m_Data;
    int                      m_DistMin;
    int                      m_DistMax;
    uint64_t                 m_Count;
};
//=================================================================================================
class CCustomer
{
public:
    virtual                  ~CCustomer                    ( void ) = default;
    virtual AFITCoin         FITCoinGen                    ( void ) = 0;
    virtual ACVUTCoin        CVUTCoinGen                   ( void ) = 0;

    virtual void             FITCoinAccept                 ( AFITCoin          x ) = 0;
    virtual void             CVUTCoinAccept                ( ACVUTCoin         x ) = 0;
};
//=================================================================================================
#endif /* __PROGTEST__ */

std::mutex mu;
std::condition_variable cond;
int numberOfThreads = 2000000;
bool sendStop = false;
bool startedThread = false;

class CRig
{
public:
    static void              Solve                         ( ACVUTCoin         x );
    static void              Solve                         ( AFITCoin          x );

    CRig                          ( void );
    ~CRig                         ( void );
    void                     Start                         ( int               thrCnt );
    void                     Stop                          ( void );
    void                     AddCustomer                   ( ACustomer         c );
private:
    // todo
    static vector<int> ToBinary(uint32_t);
    static vector<int> ToBinary2(uint8_t);
    static uint64_t nChoosek( uint64_t n, uint64_t k );
    static uint32_t ToDecimal(vector<int>);
    static int EditDistance(vector<int> &,vector<int> &,int,int,int, int**);//vector<vector<int>> &);
    static int Min(int,int,int);
    vector<thread> arr;

    void AddCustomersFromQueue();

//    std::condition_variable condi,condi2;
//    bool stop;
    static int numberOfEndedSenders;
    static int currentNOfCustomers;

    thread addCustomers;

    static unsigned int size_;

    static deque<pair<ACustomer,ACVUTCoin>> CVUTcoinQueue;
    static deque<pair<ACustomer,AFITCoin>> FITcoinQueue;
    static deque<pair<ACustomer,pair<ACVUTCoin,AFITCoin>>> resultsQueue;

    void workerThreadFunction(){
        ACVUTCoin acvutCoin;
        AFITCoin afitCoin;
        ACustomer aCustomer;
        unsigned int cnt = 0;
        bool fit = false;
        while(true) {
            cnt++;
            fit = false;
            std::unique_lock<std::mutex> locker(mu);
            cond.wait(locker, [this]() { return (CVUTcoinQueue.size() > 0 || FITcoinQueue.size() > 0 || ( queueOfCustomers.empty() && (unsigned)numberOfEndedSenders == (vectorOfCustomers.size()*2)
                && sendStop) ); });
            if(CVUTcoinQueue.size() != 0 && (cnt%2==0 || FITcoinQueue.size() == 0)){
                acvutCoin = CVUTcoinQueue.front().second;
                aCustomer = CVUTcoinQueue.front().first;
                CVUTcoinQueue.pop_front();
            }
            else if(FITcoinQueue.size() != 0){
                afitCoin = FITcoinQueue.front().second;
                aCustomer = FITcoinQueue.front().first;
                FITcoinQueue.pop_front();
                fit = true;
            }
            else if(queueOfCustomers.empty() && (unsigned)numberOfEndedSenders == (vectorOfCustomers.size()*2) && sendStop){
                locker.unlock();
                cond.notify_all();
                return;
            }
            locker.unlock();
            cond.notify_all();
            if(fit){
                this->Solve(afitCoin);
//                cout << "solvedFIT" << endl;
            }
            else{
                this->Solve(acvutCoin);
//                cout << "solved" << endl;
            }

            std::unique_lock<std::mutex> locker2(mu);
            cond.wait(locker2, [this]() { return resultsQueue.size() < 100; });
            if(fit){
                resultsQueue.push_back(make_pair(aCustomer,make_pair(ACVUTCoin(),afitCoin)));
//                cout << "sendFIT" << endl;
            }
            else{
                resultsQueue.push_back(make_pair(aCustomer,make_pair(acvutCoin,AFITCoin() ) ));
//                cout << "send" << endl;
            }

            locker2.unlock();
            cond.notify_all();

        }
    }

    struct myCustormer{
        myCustormer(ACustomer _c){
            c=_c;
            nOfSentCoins = -1;
            nOfSentCVUT = -1;
            nOfSentFIT = -1;
            nOfSubmitedCoins = 0;
            doneSubmiting = false;
            stillSending = 2;
        };
        ACustomer c;

        thread sendFitToSolve;
        thread sendCVUTToSolve;
        thread sendResults;

        int nOfSentCoins;
        int nOfSentCVUT;
        int nOfSentFIT;
        int nOfSubmitedCoins;
        int stillSending;

        bool doneSubmiting;

        void sendFIT(){
            AFITCoin afitCoin;
            while (true) {
                afitCoin = this->c->FITCoinGen();
                std::unique_lock<std::mutex> locker(mu);
                cond.wait(locker, [this](){return FITcoinQueue.size() < size_;});
                if(afitCoin != NULL){
                    if(nOfSentFIT == -1){
                        nOfSentFIT = 0;
                    }
                    nOfSentFIT++;
                    //cout << "pushed to solve" << endl;
                    FITcoinQueue.push_back(make_pair(c,afitCoin));
                }
                else{
                    if(nOfSentFIT == -1){
                        nOfSentFIT = 0;
                    }
                    if(stillSending == 1){
                        nOfSentCoins = nOfSentFIT+nOfSentCVUT;
                        //cout << "nOfSentCoins" << endl;
                    }
                    //cout << "ended pushing" << endl;
                    stillSending--;
                    numberOfEndedSenders++;
                    locker.unlock();
                    cond.notify_all();
                    return;
                }
                locker.unlock();
                cond.notify_all();
            }
        }

        void sendCVUT(){
            ACVUTCoin acvutCoin;
            while (true) {
                acvutCoin = this->c->CVUTCoinGen();
                std::unique_lock<std::mutex> locker(mu);
                cond.wait(locker, [this](){return CVUTcoinQueue.size() < size_;});
                if(acvutCoin != NULL){
                    if(nOfSentCVUT == -1){
                        nOfSentCVUT = 0;
                    }
                    nOfSentCVUT++;
                    CVUTcoinQueue.push_back(make_pair(c,acvutCoin));
                }
                else{
                    if(nOfSentCVUT == -1){
                        nOfSentCVUT = 0;
                    }
                    if(stillSending == 1){
                        nOfSentCoins = nOfSentFIT+nOfSentCVUT;
                        //cout << "nOfSentCoins" << endl;
                    }
                    stillSending--;
                    numberOfEndedSenders++;
                    locker.unlock();
                    cond.notify_all();
                    return;
                }
                locker.unlock();
                cond.notify_all();
            }
        }

        void submitFITCVUT(){
            pair<ACVUTCoin,AFITCoin> p;
            ACVUTCoin acvutCoin;
            AFITCoin afitCoin;
            bool fit=false;
            while(true) {
                fit = false;
                std::unique_lock<std::mutex> locker(mu);
                cond.wait(locker, [this]() { return ((resultsQueue.size() > 0 && resultsQueue.front().first == c) || (nOfSentCoins != -1 && nOfSubmitedCoins == nOfSentCoins) ); });
                if(nOfSentCoins != -1 && nOfSubmitedCoins == nOfSentCoins){
                    doneSubmiting = true;
                    currentNOfCustomers--;
                    //cout << "done submitting" << endl;
                    locker.unlock();
                    cond.notify_all();
                    return;
                }
                if(resultsQueue.front().second.first != NULL){
                    acvutCoin = resultsQueue.front().second.first;
                    resultsQueue.pop_front();
                    //cout<<"sendCVUT;";
                }
                else{
                    afitCoin = resultsQueue.front().second.second;
                    resultsQueue.pop_front();
                    fit = true;
                    //cout <<"sendFIT";
                }
                locker.unlock();
                cond.notify_all();
                nOfSubmitedCoins++;
                if(fit){
                    this->c->FITCoinAccept(afitCoin);
                }
                else{
                    this->c->CVUTCoinAccept(acvutCoin);
                }
            }
        }

        void start(){
            sendFitToSolve = thread(&myCustormer::sendFIT,this);
            sendCVUTToSolve = thread(&myCustormer::sendCVUT,this);
            sendResults = thread(&myCustormer::submitFITCVUT,this);
        }
    };

    vector<myCustormer*> vectorOfCustomers;
    vector<myCustormer*> queueOfCustomers;
};

int CRig::numberOfEndedSenders(0);
int CRig::currentNOfCustomers(0);
unsigned int CRig::size_(100);

deque<pair<ACustomer,ACVUTCoin>> CRig::CVUTcoinQueue;
deque<pair<ACustomer,AFITCoin>> CRig::FITcoinQueue;
deque<pair<ACustomer,pair<ACVUTCoin,AFITCoin>>> CRig::resultsQueue;

CRig::CRig(void) {
    numberOfThreads = 2000000;
    sendStop = false;
    numberOfEndedSenders = 0;
    currentNOfCustomers = 0;
    size_ = 100;
    startedThread = false;
}

CRig::~CRig(void) {
    CVUTcoinQueue.clear();
    FITcoinQueue.clear();
    resultsQueue.clear();
    vectorOfCustomers.clear();
    arr.clear();
    currentNOfCustomers = 0;
    startedThread = false;
}

void CRig::Start(int thrCnt) {
    numberOfThreads = thrCnt;
    cond.notify_all();
    for(int i=0;i<thrCnt;i++){
        arr.push_back(thread(&CRig::workerThreadFunction,this));
    }
}

void CRig::Stop(void) {
    sendStop = true;
    cond.notify_all();
    //cout << "t" << endl;
//    std::unique_lock<std::mutex> locker(mu);
//    cond.wait(locker, [this]() { return doneWorking || numberOfThreads == 2000000 || numberOfThreads == 0; });
//    //cout << "done working" << endl;
//    locker.unlock();
//    cond.notify_all();
    if(addCustomers.joinable()) {
        addCustomers.join();
    }
    for(unsigned int i=0;i<vectorOfCustomers.size();i++){
        vectorOfCustomers[i]->sendCVUTToSolve.join();
        vectorOfCustomers[i]->sendFitToSolve.join();
    }
    //cout << "no troubles here" << endl;
    for(unsigned int i=0;i<arr.size();i++){
        arr[i].join();
    }
    for(unsigned int i=0;i<vectorOfCustomers.size();i++){
        vectorOfCustomers[i]->sendResults.join();
        delete vectorOfCustomers[i];
    }
//    cout << "problem" << endl;


    CVUTcoinQueue.clear();
    FITcoinQueue.clear();
    resultsQueue.clear();
    vectorOfCustomers.clear();
    arr.clear();
    sendStop = false;
    numberOfThreads = 2000000;
    //doneWorking = false;
    numberOfEndedSenders = 0;
    //numberOfEndedWorkers = 0;
    currentNOfCustomers = 0;
    size_ = 100;
    startedThread = false;
    //cout << "done" << endl;
//    cout << "problem" << endl;
    return;
}

void CRig::AddCustomersFromQueue(){
    while(true){
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [this](){return currentNOfCustomers < 5;});
        if(queueOfCustomers.empty() && sendStop){
            //cout << "queue empty" << endl;
            return;
        }
        int tmp = (int)vectorOfCustomers.size();
        for(int i=0;i<tmp;i++){
            for(unsigned int j=0;j<vectorOfCustomers.size();j++){
                if(vectorOfCustomers[j]->doneSubmiting){
                    //cout << "JOIN JOIN JOIN JOIN" << endl;
                    vectorOfCustomers[j]->sendCVUTToSolve.join();
                    vectorOfCustomers[j]->sendFitToSolve.join();
                    numberOfEndedSenders -= 2;
                    vectorOfCustomers[j]->sendResults.join();
                    delete vectorOfCustomers[j];
                    vectorOfCustomers[j] = NULL;
                    for(unsigned int k =j+1;k<vectorOfCustomers.size();k++){
                        vectorOfCustomers[k-1] = vectorOfCustomers[k];
                    }
                    vectorOfCustomers.pop_back();
                    break;
                }
            }
        }
        if(!queueOfCustomers.empty()) {
            vectorOfCustomers.push_back(NULL);
            vectorOfCustomers[vectorOfCustomers.size() - 1] = queueOfCustomers[queueOfCustomers.size() - 1];
            size_ = (unsigned int) (100 * vectorOfCustomers.size());
            queueOfCustomers.pop_back();
            currentNOfCustomers++;
            vectorOfCustomers[vectorOfCustomers.size() - 1]->start();
        }
        locker.unlock();
        cond.notify_all();
    }
}

void CRig::AddCustomer(ACustomer c) {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [this](){return true;});
    queueOfCustomers.push_back(new myCustormer(c));
    locker.unlock();
    cond.notify_all();
    if(!startedThread){
        addCustomers = thread(&CRig::AddCustomersFromQueue,this);
        startedThread = true;
    }
}

uint64_t CRig::nChoosek( uint64_t n, uint64_t k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    uint64_t result = n;
    for( uint64_t i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

vector<int> CRig::ToBinary(uint32_t value){
    vector<int> vector1;
    for(int j=0;j<32;j++){
        vector1.push_back(value%2);
        value = value/2;
    }
    return vector1;
}

vector<int> CRig::ToBinary2(uint8_t value){
    vector<int> vector1;
    for(int j=0;j<8;j++){
        vector1.push_back(value%2);
        value = value/2;
    }

    vector<int> returnVec;
    for(int i=vector1.size()-1;i>=0;i--){
        returnVec.push_back(vector1[i]);
    }
    return returnVec;
}

uint32_t CRig::ToDecimal(vector<int> v){
    uint32_t returnValue = 0;
    for(unsigned int i=0;i<v.size();i++){
        if(v[i] == 1){
            returnValue += (uint32_t)pow(2,i);
        }
    }
    return returnValue;
}

int CRig::Min(int x, int y, int z)
{
    return min(min(x, y), z);
}

int CRig::EditDistance(vector<int> & str1, vector<int> & str2 , int m ,int n, int beginFirst, int ** dpTable)//vector<vector<int>> & dpTable)
{
    if (m == beginFirst){
        dpTable[m][n] = n;
    }
    else if (n == 0){
        dpTable[m][n] = m-beginFirst;
    }
    else if(dpTable[m][n] != -1) {
        return dpTable[m][n];
    }
    else if (str1[m-1] == str2[n-1]) {
        dpTable[m][n] = EditDistance(str1, str2, m - 1, n - 1,beginFirst,dpTable);
    }
    else {
        dpTable[m][n] = 1 + Min(EditDistance(str1, str2, m, n - 1,beginFirst,dpTable),
                                EditDistance(str1, str2, m - 1, n,beginFirst,dpTable),
                                EditDistance(str1, str2, m - 1, n - 1,beginFirst,dpTable)
        );
    }
    return dpTable[m][n];
}

void CRig::Solve(ACVUTCoin x) {
    vector<int> prefixes;
    vector<vector<int>> vv;
    prefixes = ToBinary2(x->m_Data[0]);
    vv.push_back(prefixes);
    for(unsigned int i=1;i<x->m_Data.size();i++){
        vector<int> tmp = ToBinary2(x->m_Data[i]);
        vv.push_back(tmp);
        for(unsigned int j=0;j<tmp.size();j++){
            prefixes.push_back(tmp[j]);
        }
    }

    prefixes.clear();
    for(int i=(int)(vv.size()-1);i>=0;i--){
        for(unsigned int j=0;j<vv[i].size();j++){
            prefixes.push_back(vv[i][j]);
        }
    }

    vector<int> suffixes;
    for(int i=(int)(prefixes.size()-1);i>=0;i--){
        suffixes.push_back(prefixes[i]);
    }


    int ** dpTable = NULL;
    dpTable = (int **) realloc(dpTable,sizeof(int*) * (prefixes.size()+2));
    for(unsigned int i=0;i<prefixes.size()+2;i++){
        dpTable[i] = NULL;
        dpTable[i] = (int*) realloc(dpTable[i], sizeof(int) * (prefixes.size()+2));
    }
    uint64_t counter = 0;
    for(unsigned int i=0;i<prefixes.size();i++){
        for(unsigned int i=0;i<prefixes.size()+2;i++){
            for(unsigned int j=0;j<prefixes.size()+2;j++){
                dpTable[i][j] = -1;
            }
        }

        for(unsigned int j=1;j<=prefixes.size();j++){
            int tmp = EditDistance(prefixes,prefixes,prefixes.size(),j,i,dpTable);
            if(tmp >= x->m_DistMin && tmp <= x->m_DistMax){
                counter++;
            }
        }
    }
    x->m_Count = counter;
    for(unsigned int i=0;i<prefixes.size()+2;i++){
        free(dpTable[i]);
    }
    free(dpTable);
}

void CRig::Solve(AFITCoin x) {

    int numberOfSameBits = 0;

    vector<uint32_t > arr;
    if(x->m_Vectors.size() == 1){//what if size == 0?
        uint64_t sum =0;
        for(int i=0;i<=min(x->m_DistMax,32);i++){
            sum += nChoosek(32,i);
        }

        x->m_Count = sum;
        return;
    }
    else{
        std::uint32_t res_and = x->m_Vectors[0];
        std::uint32_t res_or = x->m_Vectors[0];
        for(unsigned int i=1;i<x->m_Vectors.size();i++){
            std::uint32_t value = x->m_Vectors[i];
            res_and = res_and & value;
            res_or = res_or | value;
        }

        vector<int> vecAND = ToBinary(res_and);
        vector<int> vecOR = ToBinary(res_or);


        for(int i=0;i<32;i++){
            if(vecAND[i] == 1 || vecOR[i] == 0){
                numberOfSameBits++;
            }
        }
        for(unsigned int i=0;i<x->m_Vectors.size();i++){
            vector<int> result;
            vector<int> vector1 = ToBinary(x->m_Vectors[i]);
            for(int j=0;j<32;j++){
                if(vecAND[j] != 1 && vecOR[j] != 0){
                    result.push_back(vector1[j]);
                }
            }
            arr.push_back(ToDecimal(result));
        }
    }

    uint64_t counter = 0;
    bool b = true;


    uint32_t limit = (uint32_t )(std::pow(2,32-numberOfSameBits) -1);
    for(uint32_t i=0;i<=limit;i++){
        b = true;
        int distMax = 0;
        for(unsigned int j=0;j<x->m_Vectors.size();j++){
            int tmpDist = 0;
            uint32_t res = arr[j] ^ i;

            while(res){
                if(res&1){
                    tmpDist++;
                }
                res = res>>1;
            }
            if(tmpDist > x->m_DistMax){
                b = false;
                break;
            }
            if(tmpDist > distMax){
                distMax = tmpDist;
            }
        }
        if(b){
            if(distMax == x->m_DistMax){
                counter++;
            }
            else{
                for(int j=0;j<=min(x->m_DistMax-distMax,numberOfSameBits);j++){
                    counter += nChoosek(numberOfSameBits,j);
                }
            }
        }
    }


    x->m_Count = counter;
}

#ifndef __PROGTEST__
#include "test.inc"
#endif /* __PROGTEST__ */
