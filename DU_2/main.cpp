#ifndef __PROGTEST__
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

const string oddelovac = ";,";

class CVATRegister
{
public:
    CVATRegister   ( void );
    ~CVATRegister  ( void );
    bool NewCompany(const string & name, const string & addr, const string & taxID );
    bool CancelCompany  ( const string & name, const string & addr );
    bool CancelCompany  ( const string & taxID );
    bool Invoice ( const string & taxID, unsigned int amount );
    bool Invoice ( const string & name, const string & addr, unsigned int amount );
    bool Audit( const string & name, const string & addr, unsigned int & sumIncome ) const;
    bool Audit( const string & taxID, unsigned int & sumIncome ) const;
    unsigned int  MedianInvoice  ( void ) const;

private:
    unsigned int numberOfInv;
    vector<pair<string,unsigned int>> nameAndSum;
    vector<pair<string,string>> idAndName;
    int numberOfCompanies;
    int bSearchNewCompanyName(string name);
    int bSearchNewCompanyId(string id);
    int bSearchInvName(string) const ;
    int bSearchInvId(string) const ;
    int bSearchInvIdByName(string) const;
    void pomocna(unsigned int);
    vector<unsigned int> maxHForSmallerNumbers;
    vector<unsigned int> minHForBiggerNumbers;
    int maxCount;
    int minCount;
    struct greater1{ bool operator()(const unsigned int& a,const unsigned int& b) const{ return b<a; }};
};

CVATRegister::CVATRegister() {
    numberOfInv=0;
    numberOfCompanies=0;
    maxCount=0;
    minCount=0;
}

CVATRegister::~CVATRegister  ( void ){

}

int CVATRegister::bSearchInvIdByName(string name) const {
    for(int i=0;i<numberOfCompanies;i++)
    {
        if(idAndName[i].second==name)
        {
            return i;
        }
    }
    return -1;
}

int CVATRegister::bSearchInvId(string id) const {
    int first = 0, last = numberOfCompanies - 1;
    int middle;

    while (first <= last) {
        middle = first + (last-first)/2;
        if (idAndName[middle].first == id) {
            return middle;
        }
        else if (idAndName[middle].first > id) {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return -1;
}

int CVATRegister::bSearchInvName(string name) const {
    int first = 0, last = numberOfCompanies - 1;
    int middle;

    while (first <= last) {
        middle = first + (last-first)/2;
        if (nameAndSum[middle].first == name) {
            return middle;
        }
        else if (nameAndSum[middle].first > name) {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return -1;
}

int CVATRegister::bSearchNewCompanyName(string name) {
    int first = 0, last = numberOfCompanies - 1;
    int middle;

    while (first <= last) {
        middle = first + (last-first)/2;
        if (nameAndSum[middle].first == name) {
            return -1;
        }
        else if (nameAndSum[middle].first > name) {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return first;
}

int CVATRegister::bSearchNewCompanyId(string id) {
    int first = 0, last = numberOfCompanies - 1;
    int middle;

    while (first <= last) {
        middle = first + (last-first)/2;
        if (idAndName[middle].first == id) {
            return -1;
        }
        else if (idAndName[middle].first > id) {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return first;
}

bool CVATRegister::NewCompany(const string &name, const string &addr, const string &taxID) {
    string id=taxID,nameAdr="";
    if(name=="" || addr=="" || taxID=="")
    {return false;}

    for(unsigned int i=0;i<name.length();i++) {nameAdr+=tolower(name[i]);}
    nameAdr+=oddelovac;
    for(unsigned int i=0;i<addr.length();i++) {nameAdr+=tolower(addr[i]);}

    if(!numberOfCompanies){
        nameAndSum.push_back(make_pair(nameAdr,0));
        idAndName.push_back(make_pair(taxID,nameAdr));
        numberOfCompanies++;
        return true;
    }

    int posName = bSearchNewCompanyName(nameAdr);
    if(posName == -1) {return false;}
    int posId = bSearchNewCompanyId(id);
    if(posId==-1) { return false; }

    auto it=nameAndSum.begin();
    nameAndSum.insert(it+posName,make_pair(nameAdr,0));
    auto it2=idAndName.begin();
    idAndName.insert(it2+posId,make_pair(taxID,nameAdr));
    numberOfCompanies++;
    return true;
}

unsigned int CVATRegister::MedianInvoice() const {
    if(!numberOfInv) return 0;
    if(maxCount>minCount)
    {
        return maxHForSmallerNumbers.front();
    }
    else
    {
        return minHForBiggerNumbers.front();
    }
}

void CVATRegister::pomocna(unsigned int amount)
{
    if(numberOfInv==1)
    {
        minHForBiggerNumbers.push_back(amount);
        minCount=1;
        push_heap(minHForBiggerNumbers.begin(),minHForBiggerNumbers.end(),greater1());
    }
    else if(numberOfInv==2)
    {
        if(amount>minHForBiggerNumbers.front())
        {
            unsigned int tmp = minHForBiggerNumbers.back();
            pop_heap(minHForBiggerNumbers.begin(),minHForBiggerNumbers.end(),greater1());
            minHForBiggerNumbers.pop_back();
            minHForBiggerNumbers.push_back(amount);
            maxHForSmallerNumbers.push_back(tmp);
            push_heap(minHForBiggerNumbers.begin(),minHForBiggerNumbers.end(),greater1());
            push_heap(maxHForSmallerNumbers.begin(),maxHForSmallerNumbers.end());
        }
        else
        {
            maxHForSmallerNumbers.push_back(amount);
            push_heap(maxHForSmallerNumbers.begin(),maxHForSmallerNumbers.end());
        }
        maxCount=1;minCount=1;
    }
    else
    {
        if(amount>minHForBiggerNumbers.front())
        {
            minHForBiggerNumbers.push_back(amount);
            minCount++;
            push_heap(minHForBiggerNumbers.begin(),minHForBiggerNumbers.end(),greater1());
        }
        else if(amount < maxHForSmallerNumbers.front())
        {
            maxHForSmallerNumbers.push_back(amount);
            maxCount++;
            push_heap(maxHForSmallerNumbers.begin(),maxHForSmallerNumbers.end());
        }
        else
        {
            minHForBiggerNumbers.push_back(amount);
            minCount++;
            push_heap(minHForBiggerNumbers.begin(),minHForBiggerNumbers.end(),greater1());
        }
        if(maxCount-1>minCount)
        {
            unsigned int tmp = maxHForSmallerNumbers.front();
            minHForBiggerNumbers.push_back(tmp);
            minCount++;
            push_heap(minHForBiggerNumbers.begin(),minHForBiggerNumbers.end(),greater1());
            pop_heap(maxHForSmallerNumbers.begin(),maxHForSmallerNumbers.end());
            maxHForSmallerNumbers.pop_back();
            maxCount--;
        }
        else if(minCount-1>maxCount)
        {
            unsigned int tmp = minHForBiggerNumbers.front();
            maxHForSmallerNumbers.push_back(tmp);
            push_heap(maxHForSmallerNumbers.begin(),maxHForSmallerNumbers.end());
            pop_heap(minHForBiggerNumbers.begin(),minHForBiggerNumbers.end(),greater1());
            minHForBiggerNumbers.pop_back();
            maxCount++;
            minCount--;
        }
    }
}

bool CVATRegister::Invoice ( const string & name, const string & addr, unsigned int amount )
{
    if(nameAndSum.empty() || idAndName.empty()) {return false;}
    string nameAdr="";
    for(unsigned int i=0;i<name.length();i++) {nameAdr+=tolower(name[i]);}
    nameAdr+=oddelovac;
    for(unsigned int i=0;i<addr.length();i++) {nameAdr+=tolower(addr[i]);}
    int tmp = bSearchInvName(nameAdr);
    if(tmp==-1)
    {
        return false;
    }
    nameAndSum[tmp].second+=amount;
    numberOfInv++;
    pomocna(amount);
    return true;
}

bool CVATRegister::Invoice ( const string & taxID, unsigned int amount ){
    if(nameAndSum.empty() || idAndName.empty()) {return false;}
    int tmp = bSearchInvId(taxID);
    if(tmp==-1)
    {
        return false;
    }
    tmp = bSearchInvName(idAndName[tmp].second);
    nameAndSum[tmp].second+=amount;
    numberOfInv++;
    pomocna(amount);
    return true;
}

bool CVATRegister::Audit( const string & name, const string & addr, unsigned int & sumIncome ) const
{
    sumIncome=0;
    string nameAdr="";
    for(unsigned int i=0;i<name.length();i++) {nameAdr+=tolower(name[i]);}
    nameAdr+=oddelovac;
    for(unsigned int i=0;i<addr.length();i++) {nameAdr+=tolower(addr[i]);}
    if(nameAndSum.empty() || idAndName.empty()) {return false;}
    int tmp = bSearchInvName(nameAdr);
    if(tmp==-1)
    {
        return false;
    }
    sumIncome = nameAndSum[tmp].second;
    return true;
}

bool CVATRegister::Audit( const string & taxID, unsigned int & sumIncome ) const
{
    sumIncome=0;
    if(nameAndSum.empty() || idAndName.empty()) {return false;}
    int tmp = bSearchInvId(taxID);
    if(tmp==-1)
    {
        return false;
    }
    tmp = bSearchInvName(idAndName[tmp].second);
    sumIncome = nameAndSum[tmp].second;
    return true;
}

bool CVATRegister::CancelCompany  ( const string & name, const string & addr )
{
    string nameAdr="";
    for(unsigned int i=0;i<name.length();i++) {nameAdr+=tolower(name[i]);}
    nameAdr+=oddelovac;
    for(unsigned int i=0;i<addr.length();i++) {nameAdr+=tolower(addr[i]);}
    if(nameAndSum.empty() || idAndName.empty()) {return false;}
    int tmp = bSearchInvName(nameAdr);
    if(tmp==-1)
    {
        return false;
    }
    int tmp2 = bSearchInvIdByName(nameAdr);
    nameAndSum.erase(nameAndSum.begin()+tmp);
    idAndName.erase(idAndName.begin()+tmp2);
    numberOfCompanies--;
    return true;
}

bool CVATRegister::CancelCompany  ( const string & taxID )
{
    if(nameAndSum.empty() || idAndName.empty()) {return false;}
    int tmp = bSearchInvId(taxID);
    if(tmp==-1)
    {
        return false;
    }
    int tmp2 = bSearchInvName(idAndName[tmp].second);
    idAndName.erase(idAndName.begin()+tmp);
    nameAndSum.erase(nameAndSum.begin()+tmp2);
    numberOfCompanies--;
    return true;
}

#ifndef __PROGTEST__
int main ( void )
{
    unsigned int sumIncome;

    CVATRegister b1;
    assert ( b1 . NewCompany ( "ACME", "Kolejni", "666/666/666" ) );
    assert ( b1 . NewCompany ( "ACME", "Thakurova", "666/666" ) );
    assert ( b1 . NewCompany ( "Dummy", "Thakurova", "123456" ) );
    assert ( b1 . Invoice ( "666/666", 2000 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "666/666/666", 3000 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "123456", 4000 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "aCmE", "Kolejni", 5000 ) );
    assert ( b1 . MedianInvoice () == 4000 );
    assert ( b1 . Audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
    assert ( b1 . Audit ( "123456", sumIncome ) && sumIncome == 4000 );
    assert ( b1 . CancelCompany ( "ACME", "KoLeJnI" ) );
    assert ( b1 . MedianInvoice () == 4000 );
    assert ( b1 . CancelCompany ( "666/666" ) );
    assert ( b1 . MedianInvoice () == 4000 );
    assert ( b1 . Invoice ( "123456", 100 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "123456", 300 ) );
    assert ( b1 . MedianInvoice () == 3000 );
    assert ( b1 . Invoice ( "123456", 200 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "123456", 230 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "123456", 830 ) );
    assert ( b1 . MedianInvoice () == 830 );
    assert ( b1 . Invoice ( "123456", 1830 ) );
    assert ( b1 . MedianInvoice () == 1830 );
    assert ( b1 . Invoice ( "123456", 2830 ) );
    assert ( b1 . MedianInvoice () == 1830 );
    assert ( b1 . Invoice ( "123456", 2830 ) );
    assert ( b1 . MedianInvoice () == 2000 );
    assert ( b1 . Invoice ( "123456", 3200 ) );
    assert ( b1 . MedianInvoice () == 2000 );

    CVATRegister b2;
    assert ( b2 . NewCompany ( "ACME", "Kolejni", "abcdef" ) );
    assert ( b2 . NewCompany ( "Dummy", "Kolejni", "123456" ) );
    assert ( ! b2 . NewCompany ( "AcMe", "kOlEjNi", "1234" ) );
    assert ( b2 . NewCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
    assert ( b2 . MedianInvoice () == 0 );
    assert ( b2 . Invoice ( "ABCDEF", 1000 ) );
    assert ( b2 . MedianInvoice () == 1000 );
    assert ( b2 . Invoice ( "abcdef", 2000 ) );
    assert ( b2 . MedianInvoice () == 2000 );
    assert ( b2 . Invoice ( "aCMe", "kOlEjNi", 3000 ) );
    assert ( b2 . MedianInvoice () == 2000 );
    assert ( ! b2 . Invoice ( "1234567", 100 ) );
    assert ( ! b2 . Invoice ( "ACE", "Kolejni", 100 ) );
    assert ( ! b2 . Invoice ( "ACME", "Thakurova", 100 ) );
    assert ( ! b2 . Audit ( "1234567", sumIncome ) );
    assert ( ! b2 . Audit ( "ACE", "Kolejni", sumIncome ) );
    assert ( ! b2 . Audit ( "ACME", "Thakurova", sumIncome ) );
    assert ( ! b2 . CancelCompany ( "1234567" ) );
    assert ( ! b2 . CancelCompany ( "ACE", "Kolejni" ) );
    assert ( ! b2 . CancelCompany ( "ACME", "Thakurova" ) );
    assert ( b2 . CancelCompany ( "abcdef" ) );
    assert ( b2 . MedianInvoice () == 2000 );
    assert ( ! b2 . CancelCompany ( "abcdef" ) );
    assert ( b2 . NewCompany ( "ACME", "Kolejni", "abcdef" ) );
    assert ( b2 . CancelCompany ( "ACME", "Kolejni" ) );
    assert ( ! b2 . CancelCompany ( "ACME", "Kolejni" ) );

    return 0;
    /*Pavel Jahoda*/
}
#endif /* __PROGTEST__ */
