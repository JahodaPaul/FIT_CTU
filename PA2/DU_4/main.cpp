#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

//int vyjimka=0;

class CBank
{
public:
    // default constructor
    CBank();
    // copy constructor

    CBank(CBank &);
    // destructor
    ~CBank();
    // operator =
    CBank& operator=(CBank &);
    bool NewAccount(const char * accID, int initialBalance );
    bool Transaction(const char * debAccID, const char * credAccID, int amount, const char * signature );
    bool TrimAccount(const char * accID );
    CBank &Account(const char * name) {
        int idAcc=findAcc(name);if(idAcc==-1){ throw "hmm";}else{this->balance = arr[idAcc].balance;this->currAccount=idAcc;
        }
        return *this;}
    int Balance()
    {
        return balance;
    }

    friend ostream &operator<<(ostream& o,const CBank & p){
        o << p.arr[p.currAccount].s->str() << " = " << p.balance << "\n";
        return o;
    }
private:
    int balance=0;
    int currAccount=0;
    unsigned int nOfAcc=0;
    unsigned int limit=4;
    unsigned int copy1=0;
    int findAcc(const char*);
    void createJustOneNewArr(CBank *);
    struct CBank_Data
    {
        void Init(){name=NULL;init=0;balance=0;
            newOStringStream();
        }
        void newOStringStream()
        {
            s=new ostringstream();
            (*s) << "";
        }
        char * name=NULL;
        int init=0;
        int balance=0;
        ostringstream *s;
        void free()
        {
            delete s;
        }
    };
    CBank_Data * arr = NULL;
};


CBank ** arrPointer=NULL;
int currNOfP=0;
int leftP=0;
int limitP=4;

bool CBank::NewAccount(const char *accID, int initialBalance) {
    if(findAcc(accID)==-1)
    {
        if(this->copy1)
        {
            createJustOneNewArr(this);
        }

        if(nOfAcc==limit)
        {
            limit+=4;
            arr = (CBank_Data*)realloc(arr, sizeof(arr[0]) * limit);
        }
        arr[nOfAcc].Init();

        int tmp=0;
        while(accID[tmp]!='\0')
        {
            tmp++;
        }
        arr[nOfAcc].name = (char*)realloc(arr[nOfAcc].name,sizeof(arr[nOfAcc].name[0]) * (tmp+1));
        for(int i=0;i<tmp;i++)
        {
            arr[nOfAcc].name[i]=accID[i];
        }
        arr[nOfAcc].name[tmp]='\0';
        (*arr[nOfAcc].s) << accID;
        (*arr[nOfAcc].s) << ":\n";
        (*arr[nOfAcc].s) << "   " << initialBalance << "\n";
        arr[nOfAcc].init=initialBalance;
        arr[nOfAcc].balance=initialBalance;
        nOfAcc++;
        return true;
    }
    return false;
}

bool CBank::Transaction(const char *debAccID, const char *credAccID, int amount, const char *signature) {
    int idAcc1=findAcc(debAccID);
    int idAcc2=findAcc(credAccID);
    if(idAcc1==-1||idAcc2==-1||idAcc1==idAcc2)
    {
        return false;
    }
    else
    {
        if(this->copy1)
        {
            createJustOneNewArr(this);
        }
        arr[idAcc1].balance-=amount;
        (*arr[idAcc1].s) << " - " << amount << ", to: " << credAccID << ", sign: " << signature << "\n";
        arr[idAcc2].balance+=amount;
        (*arr[idAcc2].s) << " + " << amount << ", from: " << debAccID << ", sign: " << signature << "\n";
        return true;
    }
}

bool CBank::TrimAccount(const char *accID) {
    int idAcc=findAcc(accID);
    if(idAcc!=-1)
    {
        if(this->copy1)
        {
            createJustOneNewArr(this);
        }
        arr[idAcc].init=arr[idAcc].balance;
        arr[idAcc].free();
        arr[idAcc].newOStringStream();
        (*arr[idAcc].s) << accID;
        (*arr[idAcc].s) << ":\n";
        (*arr[idAcc].s) << "   " << arr[idAcc].init << "\n";
        return true;
    }
    return false;
}

CBank::CBank() {
    if(!currNOfP)
    {
        arrPointer = (CBank**)realloc(arrPointer,sizeof(arrPointer[0])*limitP);
    }
    else if(currNOfP==limitP)
    {
        limitP+=4;
        arrPointer = (CBank**)realloc(arrPointer,sizeof(arrPointer[0])*limitP);
    }
    arr = (CBank_Data*)realloc(arr, sizeof(arr[0]) * limit);
    arrPointer[currNOfP] = this;
    currNOfP++;
    leftP++;
}

CBank::~CBank() {

    if(this->copy1==0)
    {
        for(unsigned int i=0;i<nOfAcc;i++)
        {
            free(arr[i].name);
            arr[i].free();
        }
        free(arr);
    }
    else
    {
        int tmp=0,index=0;
        for(int i=0;i<currNOfP;i++)
        {
            if (arrPointer[i] != NULL && arrPointer[i]->arr == this->arr && arrPointer[i] != this)
            {
                tmp++;
                index=i;
            }
        }
        if(tmp==1)
        {
            arrPointer[index]->copy1=0;
        }
    }
    for(int i=0;i<currNOfP;i++)
    {
        if(this == arrPointer[i])
        {
            arrPointer[i]=NULL;
        }
    }
    leftP--;
    if(!leftP)
    {
        free(arrPointer);
        arrPointer=NULL;
        currNOfP=0;
    }
}

CBank::CBank(CBank & c):CBank() {
    (*this)=c;
}

int CBank::findAcc(const char * accID) {
    int tmp=0;
    while(1)
    {
        if(accID[tmp++]=='\0')
        {
            break;
        }
    }
    for(int i=0;i<(int)nOfAcc;i++)
    {
        int tmp2=0;
        while(1)
        {
            if(arr[i].name[tmp2++]=='\0')
            {
                break;
            }
        }
        if(tmp2!=tmp){ continue;}
        bool b= true;
        for(int j=0;j<tmp;j++)
        {
            if(arr[i].name[j]!=accID[j]){
                b=false;break;
            }
        }
        if(b)
        {
            return i;
        }
    }
    return -1;
}

CBank& CBank::operator=(CBank &c) {
    if(this!=&c)
    {
        if(this->copy1==0)
        {
            for(unsigned int i=0;i<nOfAcc;i++)
            {
                free(arr[i].name);
                arr[i].free();
            }
            free(arr);
            arr=NULL;
        }
        this->nOfAcc = c.nOfAcc;
        this->limit = c.nOfAcc;
        this->currAccount=c.currAccount;
        this->balance=c.balance;
        this->arr=c.arr;
        c.copy1=1;
        this->copy1=1;
    }
    return (*this);
}

void CBank::createJustOneNewArr(CBank * c) {
    int tmp=0,index=0;
    for(int i=0;i<currNOfP;i++)
    {
        if (arrPointer[i] != NULL && arrPointer[i]->arr == c->arr && arrPointer[i] != c)
        {
            tmp++;
            index=i;
        }
    }
    CBank_Data * b=(c->arr);
    c->arr = NULL;
    c->arr = (CBank_Data *) realloc(c->arr, sizeof(c->arr[0]) * c->limit);
    for (unsigned int i = 0; i < c->nOfAcc; i++) {
        c->arr[i].Init();
        c->arr[i].balance = b[i].balance;
        c->arr[i].init = b[i].init;
        c->arr[i].name = strdup(b[i].name);
        (*c->arr[i].s) << b[i].s->str();
    }
    c->copy1 = 0;
    if(tmp==1)
    {
        arrPointer[index]->copy1=0;
    }
}

#ifndef __PROGTEST__
int main ( void )
{
    ostringstream os;
    char accCpy[100], debCpy[100], credCpy[100], signCpy[100];
    CBank x0;
    assert ( x0 . NewAccount ( "123456", 1000 ) );
    assert ( x0 . NewAccount ( "987654", -500 ) );
    assert ( x0 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
    assert ( x0 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
    assert ( x0 . NewAccount ( "111111", 5000 ) );
    assert ( x0 . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" ) );
    assert ( x0 . Account ( "123456" ). Balance ( ) ==  -2190 );
    assert ( x0 . Account ( "987654" ). Balance ( ) ==  2980 );
    assert ( x0 . Account ( "111111" ). Balance ( ) ==  4710 );
    os . str ( "" );
    os << x0 . Account ( "123456" );
    assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
    os . str ( "" );
    os << x0 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 290, from: 111111, sign: Okh6e+8rAiuT5=\n = 2980\n" ) );
    os . str ( "" );
    os << x0 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 290, to: 987654, sign: Okh6e+8rAiuT5=\n = 4710\n" ) );
    assert ( x0 . TrimAccount ( "987654" ) );
    assert ( x0 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
    os . str ( "" );
    os << x0 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   2980\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 3103\n" ) );

    CBank x2;
    strncpy ( accCpy, "123456", sizeof ( accCpy ) );
    assert ( x2 . NewAccount ( accCpy, 1000 ));
    strncpy ( accCpy, "987654", sizeof ( accCpy ) );
    assert ( x2 . NewAccount ( accCpy, -500 ));
    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 300, signCpy ) );
    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
    strncpy ( accCpy, "111111", sizeof ( accCpy ) );
    assert ( x2 . NewAccount ( accCpy, 5000 ));
    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 2890, signCpy ) );
    assert ( x2 . Account ( "123456" ). Balance ( ) ==  -2190 );
    assert ( x2 . Account ( "987654" ). Balance ( ) ==  5580 );
    assert ( x2 . Account ( "111111" ). Balance ( ) ==  2110 );
    os . str ( "" );
    os << x2 . Account ( "123456" );
    assert ( ! strcmp ( os . str () . c_str (), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n" ) );
    os . str ( "" );
    os << x2 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n = 5580\n" ) );
    os . str ( "" );
    os << x2 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n = 2110\n" ) );
    assert ( x2 . TrimAccount ( "987654" ) );
    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
    assert ( x2 . Transaction ( debCpy, credCpy, 123, signCpy ) );
    os . str ( "" );
    os << x2 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   5580\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );

    CBank x4;
    assert ( x4 . NewAccount ( "123456", 1000 ) );
    assert ( x4 . NewAccount ( "987654", -500 ) );
    assert ( !x4 . NewAccount ( "123456", 3000 ) );
    assert ( !x4 . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" ) );
    assert ( !x4 . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" ) );
    assert ( !x4 . Transaction ( "123456", "123456", 100, "Juaw7Jasdkjb5" ) );
    try
    {
        x4 . Account ( "666" ). Balance ( );
        assert ( "Missing exception !!" == NULL );
    }
    catch ( ... )
    {
    }
    try
    {
        os << x4 . Account ( "666" ). Balance ( );
        assert ( "Missing exception !!" == NULL );
    }
    catch ( ... )
    {
    }
    assert ( !x4 . TrimAccount ( "666" ) );

    CBank x6;
    assert ( x6 . NewAccount ( "123456", 1000 ) );
    assert ( x6 . NewAccount ( "987654", -500 ) );
    assert ( x6 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
    assert ( x6 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
    assert ( x6 . NewAccount ( "111111", 5000 ) );
    assert ( x6 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
    CBank x7 ( x6 );
    assert ( x6 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
    assert ( x7 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
    assert ( x6 . NewAccount ( "99999999", 7000 ) );
    assert ( x6 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
    assert ( x6 . TrimAccount ( "111111" ) );
    assert ( x6 . Transaction ( "123456", "111111", 221, "Q23wr234ER==" ) );
    os . str ( "" );
    os << x6 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   -1802\n + 221, from: 123456, sign: Q23wr234ER==\n = -1581\n" ) );
    os . str ( "" );
    os << x6 . Account ( "99999999" );
    assert ( ! strcmp ( os . str () . c_str (), "99999999:\n   7000\n + 3789, from: 111111, sign: aher5asdVsAD\n = 10789\n" ) );
    os . str ( "" );
    os << x6 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n" ) );
    os . str ( "" );
    os << x7 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );
    try
    {
        os << x7 . Account ( "99999999" ). Balance ( );
        assert ( "Missing exception !!" == NULL );
    }
    catch ( ... )
    {
    }
    os . str ( "" );
    os << x7 . Account ( "987654" );
    assert ( ! strcmp ( os . str () . c_str (), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 789, from: 111111, sign: SGDFTYE3sdfsd3W\n = 6369\n" ) );

    CBank x8;
    CBank x9;
    assert ( x8 . NewAccount ( "123456", 1000 ) );
    assert ( x8 . NewAccount ( "987654", -500 ) );
    assert ( x8 . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" ) );
    assert ( x8 . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" ) );
    assert ( x8 . NewAccount ( "111111", 5000 ) );
    assert ( x8 . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" ) );
    x9 = x8;
    assert ( x8 . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" ) );
    assert ( x9 . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" ) );
    assert ( x8 . NewAccount ( "99999999", 7000 ) );
    assert ( x8 . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" ) );
    assert ( x8 . TrimAccount ( "111111" ) );
    os . str ( "" );
    os << x8 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   -1802\n = -1802\n" ) );
    os . str ( "" );
    os << x9 . Account ( "111111" );
    assert ( ! strcmp ( os . str () . c_str (), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n" ) );

    return 0;
    /*Pavel Jahoda*/
}
#endif /* __PROGTEST__ */
