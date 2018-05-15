#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;

class CDate
{
public:
    //---------------------------------------------------------------------------------------------
    CDate( int y, int m, int d ) : m_Year ( y ), m_Month ( m ), m_Day ( d )
    {
    }
    //---------------------------------------------------------------------------------------------
    int Compare( const CDate & x ) const
    {
        if ( m_Year != x . m_Year )
            return m_Year - x . m_Year;
        if ( m_Month != x . m_Month )
            return m_Month - x . m_Month;
        return m_Day - x . m_Day;
    }
    //---------------------------------------------------------------------------------------------
    int Year ( void ) const
    {
        return m_Year;
    }
    //---------------------------------------------------------------------------------------------
    int Month ( void ) const
    {
        return m_Month;
    }
    //---------------------------------------------------------------------------------------------
    int  Day ( void ) const
    {
        return m_Day;
    }
    //---------------------------------------------------------------------------------------------
    friend ostream & operator << ( ostream & os, const CDate & x )
    {
        char oldFill = os . fill ();
        return os << setfill ( '0' ) << setw ( 4 ) << x . m_Year << "-"
                  << setw ( 2 ) << (int) x . m_Month << "-"
                  << setw ( 2 ) << (int) x . m_Day
                  << setfill ( oldFill );
    }
    //---------------------------------------------------------------------------------------------
private:
    int16_t m_Year;
    int8_t m_Month;
    int8_t m_Day;
};
#endif /* __PROGTEST__ */

int arr[5];
bool arrB[5];

const int BY_DATE = 1;
const int BY_BUYER = 2;
const int BY_SELLER = 3;
const int BY_AMOUNT = 4;
const int BY_VAT = 5;

int pridanyPoradi=0;


class CInvoice
{
public:
    CInvoice( const CDate & date, const string & seller, const string & buyer, unsigned int amount, double VAT );

    CDate Date ( void ) const;
    string Buyer ( void ) const;
    string Seller ( void ) const;
    int Amount ( void ) const;
    double VAT ( void ) const;
    bool pair=false;
    int issued1Accepted2=0;
    int pridany;
private:
    // todo
    const CDate datee;
    const string buyerr;
    const string sellerr;
    const int amountt;
    const double vatt;

    friend bool operator<(const CInvoice& in,const CInvoice& in2 )
    {
        if((!arr[0] && !arr[1] && !arr[2] && !arr[3] && !arr[4] )|| arr[0]==10) {
            if(arr[0]==10)
            {
                return in.pridany < in2.pridany;
            } else{
                if (in.Buyer() != in2.Buyer()) {
                    return in.Buyer() < in2.Buyer();
                } else if (in.Seller() != in2.Seller()) {
                    return in.Seller() < in2.Seller();
                } else if (in.VAT() != in2.VAT()) {
                    return in.VAT() < in2.VAT();
                } else if (in.Amount() != in2.Amount()) {
                    return in.Amount() < in2.Amount();
                }
                    if (in.Date().Compare(in2.Date()) > 0) {
                        return true;
                    } else {
                        return false;
                    }
            }
        }
        else
        {
            for(int i=0;i<5;i++)
            {
                if(!arr[i])
                {
                    break;
                }
                if(arr[i]==BY_VAT)
                {
                    if (in.VAT() != in2.VAT()) {
                        if (!arrB[i]) {
                            return in2.VAT() < in.VAT();
                        } else {
                                return in.VAT() < in2.VAT();
                        }
                    }
                }
                else if(arr[i]==BY_AMOUNT) {
                    if (in.Amount() != in2.Amount()) {
                        if (!arrB[i]) {
                            return in2.Amount() < in.Amount();
                    } else {
                            return in.Amount() < in2.Amount();
                        }
                    }
                }
                else if(arr[i]==BY_BUYER)
                {
                    string seller1=in.Buyer();
                    string seller2=in2.Buyer();
                    std::transform(seller1.begin(), seller1.end(),seller1.begin(), ::toupper);
                    std::transform(seller2.begin(), seller2.end(),seller2.begin(), ::toupper);
                    if (seller1 != seller2)
                    {
                        if(!arrB[i]) {
                            return seller2 < seller1;
                        } else{
                            return seller1 < seller2;
                        }
                    }
                }
                else if(arr[i]==BY_SELLER)
                {
                    string seller1=in.Seller();
                    string seller2=in2.Seller();
                    std::transform(seller1.begin(), seller1.end(),seller1.begin(), ::toupper);
                    std::transform(seller2.begin(), seller2.end(),seller2.begin(), ::toupper);
                    if (seller1 != seller2)
                    {
                        if(!arrB[i]) {
                            return seller2 < seller1;
                        } else{
                            return seller1 < seller2;
                        }
                    }
                }
                else if(arr[i]==BY_DATE)
                {
                    if(in.Date().Compare(in2.Date()) != 0) {
                        if (in.Date().Compare(in2.Date()) > 0) {
                            return !arrB[i];
                        } else {
                            return arrB[i];
                        }
                    }
                }

            }
            return in.pridany < in2.pridany;
        }
    }
};

CInvoice::CInvoice(const CDate &date, const string &seller, const string &buyer, unsigned int amount, double VAT)
:datee(date),buyerr(buyer),sellerr(seller),amountt(amount),vatt(VAT){
    pridany=pridanyPoradi;
}

CDate CInvoice::Date(void) const {
    return datee;
}

string CInvoice::Buyer(void) const {
    return buyerr;
}

string CInvoice::Seller(void) const {
    return sellerr;
}

int CInvoice::Amount(void) const {
    return amountt;
}

double CInvoice::VAT(void) const {
    return vatt;
}


class CSortOpt
{
public:
    static const int BY_DATE = 0;
    static const int BY_BUYER = 1;
    static const int BY_SELLER = 2;
    static const int BY_AMOUNT = 3;
    static const int BY_VAT = 4;
    CSortOpt ( void );
    CSortOpt & AddKey ( int key, bool ascending = true );
private:

};

CSortOpt::CSortOpt(void) {
}

CSortOpt &CSortOpt::AddKey(int key, bool ascending) {
    if(!arr[0]){arr[0]=(key+1);arrB[0]=ascending;return (*this);}
    if(!arr[1]){arr[1]=(key+1);arrB[1]=ascending;return (*this);}
    if(!arr[2]){arr[2]=(key+1);arrB[2]=ascending;return (*this);}
    if(!arr[3]){arr[3]=(key+1);arrB[3]=ascending;return (*this);}
    if(!arr[4]){arr[4]=(key+1);arrB[4]=ascending;return (*this);}
    return (*this);
}

class CVATRegister
{
public:
    CVATRegister ( void );
    bool RegisterCompany ( const string & name );
    bool AddIssued ( const CInvoice  & x );
    bool AddAccepted ( const CInvoice  & x );
    bool DelIssued ( const CInvoice  & x );
    bool DelAccepted ( const CInvoice  & x );
    list<CInvoice> Unmatched ( const string & company, const CSortOpt  & sortBy );
private:
    map<string,map<CInvoice,CInvoice> > mapa;
    set<CInvoice>::iterator itSet;
    string pomocna(const string & name);
    map<string,string> pomocnaMapa;
};

CVATRegister::CVATRegister(void) {
}

bool CVATRegister::RegisterCompany(const string &name) {
    string tmp = pomocna(name);
    auto it = mapa.find(tmp);
    if(it!=mapa.end())
    {
        return false;
    }
    map <CInvoice,CInvoice> s;
    mapa.insert(make_pair(tmp,s));
    pomocnaMapa.insert(make_pair(tmp,name));
    return true;
}


bool CVATRegister::AddIssued(const CInvoice &x) {

    string tmp = pomocna(x.Seller());
    auto it = mapa.find(tmp);
    string tmp2=pomocna(x.Buyer());
    auto it2=mapa.find(tmp2);
    if(it2==mapa.end() || it==mapa.end() || tmp==tmp2)
    {
        return false;
    }
    auto it3=pomocnaMapa.find(tmp);
    auto it4=pomocnaMapa.find(tmp2);
    bool b1=true,b2=true;
    CInvoice c(x.Date(),(*it3).second,(*it4).second,x.Amount(),x.VAT());
    int tmpPridany=pridanyPoradi;
    if((*it).second.insert(make_pair(c,c)).second== false)
    {
        auto find = (*it).second.find(c);
        if((*find).second.issued1Accepted2==1 || (*find).second.pair==true)
        {
            return false;
        }
        (*find).second.pair=true;
        pridanyPoradi++;
        b1=false;
    }
    if((*it2).second.insert(make_pair(c,c)).second==false)
    {
        auto find = (*it2).second.find(c);
        if(pridanyPoradi>tmpPridany){pridanyPoradi--;}
        if((*find).second.issued1Accepted2==1 || (*find).second.pair==true)
        {
            return false;
        }
        (*find).second.pair=true;
        pridanyPoradi++;
        b2=false;
    }
    if(b1)
    {
        auto find = (*it).second.find(c);
        (*find).second.issued1Accepted2=1;
        if(pridanyPoradi>tmpPridany){pridanyPoradi--;}
        pridanyPoradi++;
    }
    if(b2)
    {
        auto find = (*it2).second.find(c);
        (*find).second.issued1Accepted2=1;
        if(pridanyPoradi>tmpPridany){pridanyPoradi--;}
        pridanyPoradi++;
    }
    return true;
}

bool CVATRegister::AddAccepted(const CInvoice &x) {
    string tmp = pomocna(x.Seller());
    auto it = mapa.find(tmp);
    string tmp2=pomocna(x.Buyer());
    auto it2=mapa.find(tmp2);
    if(it2==mapa.end() || it==mapa.end() || tmp==tmp2)
    {
        return false;
    }
    bool b1=true,b2=true;
    auto it3=pomocnaMapa.find(tmp);
    auto it4=pomocnaMapa.find(tmp2);
    int tmpPridany=pridanyPoradi;
    CInvoice c(x.Date(),(*it3).second,(*it4).second,x.Amount(),x.VAT());
    if((*it).second.insert(make_pair(c,c)).second== false)
    {
        auto find = (*it).second.find(c);
        if((*find).second.issued1Accepted2==2 || (*find).second.pair==true)
        {
            return false;
        }
        (*find).second.pair=true;
        pridanyPoradi++;
        b1=false;
    }
    if((*it2).second.insert(make_pair(c,c)).second==false)
    {
        auto find = (*it2).second.find(c);
        if(pridanyPoradi>tmpPridany){pridanyPoradi--;}
        if((*find).second.issued1Accepted2==2 || (*find).second.pair==true)
        {
            return false;
        }
        (*find).second.pair=true;
        pridanyPoradi++;
        b2=false;
    }
    if(b1)
    {
        auto find = (*it).second.find(c);
        (*find).second.issued1Accepted2=2;
        if(pridanyPoradi>tmpPridany){pridanyPoradi--;}
        pridanyPoradi++;
    }
    if(b2)
    {
        auto find = (*it2).second.find(c);
        (*find).second.issued1Accepted2=2;
        if(pridanyPoradi>tmpPridany){pridanyPoradi--;}
        pridanyPoradi++;
    }
    return true;
}

list<CInvoice> CVATRegister::Unmatched(const string &company, const CSortOpt &sortBy) {
    if(!arr[0])
    {
        arr[0]=10;
    }
    map<CInvoice,CInvoice> copyMapa;
    string tmp = pomocna(company);
    auto it = mapa.find(tmp);
    list<CInvoice> list;
    if(it==mapa.end())
    {
        arr[0]=0;
        return list;
    }
    for (auto itt = (*it).second.begin(); itt != (*it).second.end(); ++itt) {
        copyMapa.insert(*itt);
    }

    for (auto i = copyMapa.begin(); i != copyMapa.end(); ++i) {
        if(!(*i).second.pair)
        {
            list.push_back((*i).second);
        }
    }
    for(int i=0;i<5;i++)
    {
        arr[i]=0;
        arrB[i]=false;
    }
    return list;
}

bool CVATRegister::DelIssued(const CInvoice &x) {
    string tmp = pomocna(x.Seller());
    auto it = mapa.find(tmp);
    string tmp2=pomocna(x.Buyer());
    auto it2=mapa.find(tmp2);

    if(it2==mapa.end() || it==mapa.end() || tmp==tmp2)
    {
        return false;
    }
    auto it3=pomocnaMapa.find(tmp);
    auto it4=pomocnaMapa.find(tmp2);
    CInvoice c(x.Date(),(*it3).second,(*it4).second,x.Amount(),x.VAT());

    auto found1= (*it).second.find(c);
    auto found2= (*it2).second.find(c);
    if(found1==(*it).second.end())
    {
        return false;
    }
    if((*found1).second.pair==true)
    {
        (*found1).second.pair=false;
        (*found1).second.issued1Accepted2=2;
        (*found2).second.pair=false;
        (*found2).second.issued1Accepted2=2;
    }
    else if((*found1).second.issued1Accepted2==2)
    {
        return false;
    }
    else if((*found1).second.issued1Accepted2==1)
    {
        (*it).second.erase(c);
        (*it2).second.erase(c);
    }
    return true;
}

bool CVATRegister::DelAccepted(const CInvoice &x) {
    string tmp = pomocna(x.Seller());
    auto it = mapa.find(tmp);
    string tmp2=pomocna(x.Buyer());
    auto it2=mapa.find(tmp2);

    if(it2==mapa.end() || it==mapa.end() || tmp==tmp2)
    {
        return false;
    }
    auto it3=pomocnaMapa.find(tmp);
    auto it4=pomocnaMapa.find(tmp2);
    CInvoice c(x.Date(),(*it3).second,(*it4).second,x.Amount(),x.VAT());

    auto found1= (*it).second.find(c);
    auto found2= (*it2).second.find(c);
    if(found1==(*it).second.end())
    {
        return false;
    }
    if((*found1).second.pair==true)
    {
        (*found1).second.pair=false;
        (*found1).second.issued1Accepted2=1;
        (*found2).second.pair=false;
        (*found2).second.issued1Accepted2=1;
    }
    else if((*found1).second.issued1Accepted2==1)
    {
        return false;
    }
    else if((*found1).second.issued1Accepted2==2)
    {
        (*it).second.erase(c);
        (*it2).second.erase(c);
    }
    return true;
}

string CVATRegister::pomocna(const string &name) {
    string nameCopy=name;
    string tm = "";
    int l=name.length();
    bool b=false;
    for(int i=0;i<l;i++)
    {
        int s=0;
        while(nameCopy[i]==' ' && i<l)
        {
            s++;
            i++;
        }
        if(nameCopy[i]!=' ' && i<l)
        {
            if(s && b)
            {
                tm+='T';
            }
            tm+=tolower(nameCopy[i]);
            b=true;
        }
    }
    return tm;
}

#ifndef __PROGTEST__
bool equalLists ( const list<CInvoice> & a, const list<CInvoice> & b )
{
    list<CInvoice> c=a;
    list<CInvoice> d=b;
    if(a.size() != b.size())
    {
        return false;
    }
    list<CInvoice>::const_iterator it;
    list<CInvoice>::const_iterator it2;
    for (it = a.begin(),it2=b.begin(); it != a.end(); ++it,++it2) {
        if((*it).Buyer() != (*it2).Buyer() || (*it).Seller() != (*it2).Seller() || (*it).Amount() != (*it2).Amount() || (*it).VAT() != (*it2).VAT() || (*it).Date().Compare((*it2).Date()) != 0)
        {
            return false;
        }
    }
    return true;
}

int main ( void )
{
    CVATRegister r;
    assert ( r . RegisterCompany ( "first Company" ) );
    assert ( r . RegisterCompany ( "Second     Company" ) );
    assert ( r . RegisterCompany ( "ThirdCompany, Ltd." ) );
    assert ( r . RegisterCompany ( "Third Company, Ltd." ) );
    assert ( !r . RegisterCompany ( "Third Company, Ltd." ) );
    assert ( !r . RegisterCompany ( " Third  Company,  Ltd.  " ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 20 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "FirSt Company", "Second Company ", 200, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Second Company ", "First Company", 300, 30 ) ) );
    assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34 ) ) );
    assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "First Company", "First   Company", 200, 30 ) ) );
    assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "Another Company", "First   Company", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, false ) . AddKey ( CSortOpt::BY_DATE, false ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_DATE, true ) . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_VAT, true ) . AddKey ( CSortOpt::BY_AMOUNT, true ) . AddKey ( CSortOpt::BY_DATE, true ) . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . Unmatched ( "second company", CSortOpt () . AddKey ( CSortOpt::BY_DATE, false ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Third Company, Ltd.", "Second     Company", 400, 34.000000 )
                                  } ) );
    assert ( equalLists ( r . Unmatched ( "last company", CSortOpt () . AddKey ( CSortOpt::BY_VAT, true ) ),
                          list<CInvoice>
                                  {
                                  } ) );
    assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company ", 200, 30 ) ) );
    assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "Second company ", "First Company", 300, 32 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2001, 1, 1 ), "First Company", "Second Company ", 200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "A First Company", "Second Company ", 200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Hand", 200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 1200, 30 ) ) );
    assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 200, 130 ) ) );
    assert ( r . DelIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
    assert ( r . DelAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
    assert ( r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
    return 0;
    /*Pavel Jahoda*/
}
#endif /* __PROGTEST__ */
