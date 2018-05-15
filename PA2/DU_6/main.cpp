#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */




class OrderingDoesNotExistException
{
public:
    OrderingDoesNotExistException()
    {

    }
};

class DuplicateMatchException
{
public:
    DuplicateMatchException()
    {

    }
};

template <typename _M>
class CContest
{
public:
    // default constructor
    CContest(){};
    // destructor
    ~CContest(){};

    // IsOrdered ( comparator )
    bool IsOrdered (const int (*comparator)(const _M& x)) const
    {
        CompWrapper myComp(comparator);
        return IsOrdered<CompWrapper>(myComp);
    }
    template<class TC>
    bool IsOrdered(const TC& comp) const
    {
        int l=matches1.size();
        vector<int> nOfPlayersPoint = nOfPlayersPointingToIt;
        vector<set<int> > vv=v;
        for(int i=0;i<l;i++)
        {
            int result = comp(matches2[i]);
            int hrac1=0;
            int hrac2=0;
            hrac2=matches1[i]%10000;
            if(matches1[i]>=10000)
            {
                hrac1=matches1[i]/10000;
            }
            if(result>0){
                nOfPlayersPoint[hrac1]-=1;
                vv[hrac2].erase(hrac1);
            }
            else if(result<0)
            {
                nOfPlayersPoint[hrac2]-=1;
                vv[hrac1].erase(hrac2);
            }
            else{
                nOfPlayersPoint[hrac1]-=1;
                nOfPlayersPoint[hrac2]-=1;
                vv[hrac1].erase(hrac2);
                vv[hrac2].erase(hrac1);
            }
        }
        bool b=false;
        while(!b)
        {
            int index=0;
            bool pomocna=false;
            bool konec=true;
            for(unsigned int i=0;i<nOfPlayersPoint.size();i++)
            {
                if(nOfPlayersPoint[i]==0)
                {
                    if(pomocna==true)
                    {
                        return false;
                    }
                    pomocna=true;
                    index=i;
                }
                if(nOfPlayersPoint[i]!=-1)
                {
                    konec=false;
                }
            }
            if(konec)
            {
                b=true;
                break;
            }
            if(!pomocna)
            {
                return false;
            }
            for(std::set<int>::iterator it = vv[index].begin(); it != vv[index].end(); ++it) {
                nOfPlayersPoint[(*it)]-=1;
            }
            vv[index].clear();
            nOfPlayersPoint[index]=-1;
        }
        return true;
    }
    // Results ( comparator )
    list<string> Results(const int (*comparator)(const _M& x)) const
    {
        CompWrapper myComp(comparator);
        return Results<CompWrapper>(myComp);
    }
    template<class TC>
    list<string> Results(const TC& comp) const
    {
        list<string> res;
        int l=matches1.size();
        vector<int> nOfPlayersPoint = nOfPlayersPointingToIt;
        vector<set<int> > vv=v;
        for(int i=0;i<l;i++)
        {
            int result = comp(matches2[i]);
            int hrac1=0;
            int hrac2=0;
            hrac2=matches1[i]%10000;
            if(matches1[i]>=10000)
            {
                hrac1=matches1[i]/10000;
            }
            if(result>0){
                nOfPlayersPoint[hrac1]-=1;
                vv[hrac2].erase(hrac1);
            }
            else if(result<0)
            {
                nOfPlayersPoint[hrac2]-=1;
                vv[hrac1].erase(hrac2);
            }
            else{
                nOfPlayersPoint[hrac1]-=1;
                nOfPlayersPoint[hrac2]-=1;
                vv[hrac1].erase(hrac2);
                vv[hrac2].erase(hrac1);
            }
        }
        bool b=false;
        while(!b)
        {
            int index=0;
            bool pomocna=false;
            bool konec=true;
            for(unsigned int i=0;i<nOfPlayersPoint.size();i++)
            {
                if(nOfPlayersPoint[i]==0)
                {
                    if(pomocna==true)
                    {
                        throw OrderingDoesNotExistException();
                    }
                    pomocna=true;
                    index=i;
                }
                if(nOfPlayersPoint[i]!=-1)
                {
                    konec=false;
                }
            }
            if(konec)
            {
                b=true;
                break;
            }
            if(!pomocna)
            {
                throw OrderingDoesNotExistException();
            }
            for(std::set<int>::iterator it = vv[index].begin(); it != vv[index].end(); ++it) {
                nOfPlayersPoint[(*it)]-=1;
            }
            vv[index].clear();
            nOfPlayersPoint[index]=-1;
            auto itt = mapaIndexuHracuAJmen.find(index);
            res.push_back((*itt).second);
        }
        return res;
    }

    // AddMatch ( contestant1, contestant2, result )
    CContest &AddMatch(const string a,const string b,const _M& x)
    {
        int hrac1=0,hrac2=0,p=pocethracu;
        auto it = mapaJmenHracuAIndexu.find(a);
        if(it==mapaJmenHracuAIndexu.end())
        {
            mapaJmenHracuAIndexu.insert(make_pair(a,pocethracu));
            mapaIndexuHracuAJmen.insert(make_pair(pocethracu,a));
            hrac1=pocethracu;
            pocethracu++;
        }
        else
        {
            hrac1=(*it).second;
        }
        auto it2 = mapaJmenHracuAIndexu.find(b);
        if(it2==mapaJmenHracuAIndexu.end())
        {
            mapaJmenHracuAIndexu.insert(make_pair(b,pocethracu));
            mapaIndexuHracuAJmen.insert(make_pair(pocethracu,b));
            hrac2=pocethracu;
            pocethracu++;
        }
        else
        {
            hrac2=(*it2).second;
        }

        //pokud neni nejaky duplikat - musi se dodelat
        int tmp = hrac1*10000+hrac2;
        for(unsigned int i=0;i<matches1.size();i++)
        {
            int hracTmp1=0;
            int hracTmp2=0;
            hracTmp2=matches1[i]%10000;
            if(matches1[i]>=10000)
            {
                hracTmp1=matches1[i]/10000;
            }
            if( (hrac1==hracTmp1&&hrac2==hracTmp2) || (hrac2==hracTmp1&&hrac1==hracTmp2) )
            {
                throw DuplicateMatchException();
            }
        }
        matches1.push_back(tmp);
        matches2.push_back(x);
        if(p==hrac1)
        {
            p++;
            v.push_back(set<int>());
            v[hrac1].insert(hrac2);
            nOfPlayersPointingToIt.push_back(0);
            nOfPlayersPointingToIt[hrac1] += 1;
        }
        else
        {
            nOfPlayersPointingToIt[hrac1] += 1;
            v[hrac1].insert(hrac2);
        }
        if(p==hrac2)
        {
            v.push_back(set<int>());
            v[hrac2].insert(hrac1);
            nOfPlayersPointingToIt.push_back(0);
            nOfPlayersPointingToIt[hrac2] += 1;
        }
        else
        {
            nOfPlayersPointingToIt[hrac2] += 1;
            v[hrac2].insert(hrac1);
        }
        return *this;
    }

private:
    class CompWrapper
    {
    private:
        int (*comparator)(const _M& x);
    public:
        CompWrapper(const int (*c)(const _M& x))
        {
            comparator = c;
        }
        int operator () ( const _M & x ) const
        {
            return comparator(x);
        }
    };
    int pocethracu=0;
    vector<int> matches1;
    vector<_M> matches2;
    vector<int> nOfPlayersPointingToIt;
    map<string,int> mapaJmenHracuAIndexu;
    map<int,string> mapaIndexuHracuAJmen;
    vector<set<int> > v;
};

#ifndef __PROGTEST__
struct CMatch
{
    public:CMatch( int a, int b ) : m_A ( a ), m_B ( b ) {}
    int m_A;
    int m_B;
};

class HigherScoreThreshold
{
public:
    HigherScoreThreshold ( int diffAtLeast ) : m_DiffAtLeast ( diffAtLeast )
    {
    }
    int operator () ( const CMatch & x ) const
    {
        return ( x . m_A > x . m_B + m_DiffAtLeast ) - ( x . m_B > x . m_A + m_DiffAtLeast );
    }
private:
    int m_DiffAtLeast;
};

int HigherScore( const CMatch & x )
{
    return ( x . m_A > x . m_B ) - ( x . m_B > x . m_A );
}

int main ( void )
{
    CContest<CMatch>  x;

    x . AddMatch ( "C++", "Pascal", CMatch ( 10, 3 ) )
            . AddMatch ( "C++", "Java", CMatch ( 8, 1 ) )
            . AddMatch ( "Pascal", "Basic", CMatch ( 40, 0 ) )
            . AddMatch ( "Java", "PHP", CMatch ( 6, 2 ) )
            . AddMatch ( "Java", "Pascal", CMatch ( 7, 3 ) )
            . AddMatch ( "PHP", "Basic", CMatch ( 10, 0 ) );


    assert ( ! x . IsOrdered ( HigherScore ) );

    try
    {
        list<string> res = x . Results ( HigherScore );
        assert ( "Exception missing!" == NULL );
    }
    catch ( const OrderingDoesNotExistException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == NULL );
    }

    x . AddMatch ( "PHP", "Pascal", CMatch ( 3, 6 ) );

    assert ( x . IsOrdered ( HigherScore ) );
    try
    {
        list<string> res = x . Results ( HigherScore );
        assert ( ( res == list<string>{ "C++", "Java", "Pascal", "PHP", "Basic" } ) );
    }
    catch ( ... )
    {
        assert ( "Unexpected exception!" == NULL );
    }


    assert ( ! x . IsOrdered ( HigherScoreThreshold ( 3 ) ) );
    try
    {
        list<string> res = x . Results ( HigherScoreThreshold ( 3 ) );
        assert ( "Exception missing!" == NULL );
    }
    catch ( const OrderingDoesNotExistException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == NULL );
    }

    assert ( x . IsOrdered ( [] ( const CMatch & x )
                             {
                                 return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A );
                             } ) );
    try
    {
        list<string> res = x . Results ( [] ( const CMatch & x )
                                         {
                                             return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A );
                                         } );
        assert ( ( res == list<string>{ "Basic", "PHP", "Pascal", "Java", "C++" } ) );
    }
    catch ( ... )
    {
        assert ( "Unexpected exception!" == NULL );
    }

    CContest<bool>  y;

    y . AddMatch ( "Python", "PHP", true )
            . AddMatch ( "PHP", "Perl", true )
            . AddMatch ( "Perl", "Bash", true )
            . AddMatch ( "Bash", "JavaScript", true )
            . AddMatch ( "JavaScript", "VBScript", true );

    assert ( y . IsOrdered ( [] ( bool v )
                             {
                                 return v ? 10 : - 10;
                             } ) );
    try
    {
        list<string> res = y . Results ( [] ( bool v )
                                         {
                                             return v ? 10 : - 10;
                                         });
        assert ( ( res == list<string>{ "Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript" } ) );
    }
    catch ( ... )
    {
        assert ( "Unexpected exception!" == NULL );
    }

    y . AddMatch ( "PHP", "JavaScript", false );
    assert ( !y . IsOrdered ( [] ( bool v )
                              {
                                  return v ? 10 : - 10;
                              } ) );
    try
    {
        list<string> res = y . Results ( [] ( bool v )
                                         {
                                             return v ? 10 : - 10;
                                         } );
        assert ( "Exception missing!" == NULL );
    }
    catch ( const OrderingDoesNotExistException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == NULL );
    }

    try
    {
        y . AddMatch ( "PHP", "JavaScript", false );
        assert ( "Exception missing!" == NULL );
    }
    catch ( const DuplicateMatchException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == NULL );
    }

    try
    {
        y . AddMatch ( "JavaScript", "PHP", true );
        assert ( "Exception missing!" == NULL );
    }
    catch ( const DuplicateMatchException & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == NULL );
    }
    return 0;
    /*Pavel Jahoda*/
}
#endif /* __PROGTEST__ */
