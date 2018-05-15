#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

ios_base & dummy_polynomial_manipulator ( ios_base & x )
{
    return x;
}

ios_base & ( * ( polynomial_variable ( const string & varName ) ) ) ( ios_base & x )
{
    return dummy_polynomial_manipulator;
}
class CPolynomial
{
public:
    // default constructor
    CPolynomial();
    // operator +
    CPolynomial operator+(const CPolynomial) const;
    // operator -
    CPolynomial operator-(const CPolynomial) const;
    // operator * (polynomial, double)
    CPolynomial operator*(const long double) const;
    CPolynomial operator*(const CPolynomial) const;
    // operator ==
    bool operator==(const CPolynomial) const;
    // operator !=
    bool operator!=(const CPolynomial) const;
    // operator []
    long double & operator[](const int);
    long double operator[] ( const int ind ) const {
        return this->v[ind];
    }
    // operator ()
    long double operator()(const long double) const;
    // operator <<
    friend ostream &operator<<(ostream& o,const CPolynomial & p){
        bool b= false;
        if(p.maximum==1 && p.v[0]==0)
        {
            o<<"0";
            return o;
        }
        bool prazdno=true;
        for(int i=0;i<p.maximum;i++)
        {
            if(p[i]!=0)
            {
                prazdno=false;
                break;
            }
        }
        if(prazdno)
        {
            o<<"0";
            return o;
        }
        for(int i=p.maximum-1;i>=0;i--)
        {
            if(p.v[i]!=0)
            {
                if(!b)
                {
                    if(p.v[i]<0)
                    {
                        o << "- ";
                    }

                    if((p.v[i]== -1 || p.v[i]==1) && i!=0)
                    {
                        o << "x^" << i;
                    }
                    else if(i!=0)
                    {
                        if(p.v[i] < 0){o << (-1*p.v[i]);}
                        else {o << p.v[i];}
                        o << "*x^" << i;
                    }
                    else{
                        if(p.v[i] < 0){o << (-1*p.v[i]);}
                        else {o << p.v[i];}
                    }
                    b=true;
                }
                else
                {
                    if(p.v[i]<0)
                    {
                        o << " - ";
                    }
                    else
                    {
                        o << " + ";
                    }

                    if((p.v[i]== -1 || p.v[i]==1) && i!=0)
                    {
                        o << "x^" << i;
                    }
                    else if(i!=0)
                    {
                        if(p.v[i] < 0){o << (-1*p.v[i]);}
                        else {o << p.v[i];}
                        o << "*x^" << i;
                    }
                    else{
                        if(p.v[i] < 0){o << (-1*p.v[i]);}
                        else {o << p.v[i];}
                    }
                }
            }
        }
        return o;
    }
    // Degree (), returns unsigned value
    int Degree() const
    {
        int i=0;
        for (i = this->maximum;i > 0;i--)
        {
            if(this->v[i] != 0)
            {
                break;
            }
        }
        return i;
    }
    CPolynomial& operator=(const CPolynomial&);
    long double v[10000];
private:
    int maximum=1;
};

CPolynomial::CPolynomial(){
    for(int i=0;i<10000;i++)
    {
        this->v[i]=0;
    }
}

CPolynomial CPolynomial::operator+(const CPolynomial p)const {
    CPolynomial newP;
    int n=0;
    if(this->maximum > p.maximum)
    {
        n=this->maximum;
    }
    else
    {
        n=p.maximum;
    }
    for(int i=0;i<n;i++)
    {
        newP.v[i] = this->v[i] + p.v[i];
    }
    for(int i=n-1;i>=0;i--)
    {
        if(newP.v[i]!=0)
        {
            newP.maximum=i+1;
            break;
        }
    }
    return newP;
}

CPolynomial CPolynomial::operator-(const CPolynomial p)const {
    CPolynomial newP;
    int n=0;
    if(this->maximum > p.maximum)
    {
        n=this->maximum;
    }
    else
    {
        n=p.maximum;
    }
    for(int i=0;i<n;i++)
    {
        newP.v[i] = this->v[i] - p.v[i];
    }
    for(int i=n-1;i>=0;i--)
    {
        if(newP.v[i]!=0)
        {
            newP.maximum=i+1;
            break;
        }
    }
    return newP;
}

long double & CPolynomial::operator[](const int a) {
    if(a>=10000 || a<0)
    {
        return v[9999];
    }
    if(a>=(this->maximum))
    {
        this->maximum=a+1;
    }
    return v[a];
}

long double CPolynomial::operator()(const long double n) const{
    long double result=0;
    for(int i=0;i<maximum;i++)
    {
        if(v[i]!=0)
        {
            long double tmp=n;
            if(i==0)
            {
                tmp=1;
            }
            for(int j=0;j<i-1;j++)
            {
                tmp*=n;
            }
            result+=(tmp*v[i]);
        }
    }
    return result;
}

CPolynomial CPolynomial::operator*(const long double d)const {
    CPolynomial newP;
    newP.maximum=this->maximum;
    for(int i=0;i<maximum;i++)
    {
        newP.v[i]=this->v[i]*d;
    }
    return newP;
}

CPolynomial CPolynomial::operator*(const CPolynomial p)const {
    CPolynomial newP;
    for(int i=0;i<this->maximum;i++)
    {
        for(int j=0;j<p.maximum;j++)
        {
            if(i+j<10000)
            {
                newP.v[i+j]+= (this->v[i]*p.v[j]);
            }
        }
    }
    for(int i=0;i<9999;i++)
    {
        if(newP.v[i]!=0)
        {
            newP.maximum=i+1;
        }
    }
    return newP;
}

bool CPolynomial::operator==(const CPolynomial p) const {
    if(this->maximum > p.maximum){
        for(int i=0;i<this->maximum;i++)
        {
            if(this->v[i] != p.v[i] && ( (this->v[i]>p.v[i] && this->v[i]-0.000001 > p.v[i]) || (this->v[i]<p.v[i] && this->v[i]+0.000001 < p.v[i]) ) )
            {
                return false;
            }
        }
    }
    else{
        for(int i=0;i<p.maximum;i++)
        {
            if(this->v[i] != p.v[i] && ( (this->v[i]>p.v[i] && this->v[i]-0.000001 > p.v[i]) || (this->v[i]<p.v[i] && this->v[i]+0.000001 < p.v[i]) ) )
            {
                return false;
            }
        }
    }

    return true;
}

bool CPolynomial::operator!=(const CPolynomial p) const {
    if(this->maximum > p.maximum){
        for(int i=0;i<this->maximum;i++)
        {
            if(this->v[i] != p.v[i] && ( (this->v[i]>p.v[i] && this->v[i]-0.000001 > p.v[i]) || (this->v[i]<p.v[i] && this->v[i]+0.000001 < p.v[i]) ) )
            {
                return true;
            }
        }
    }
    else{
        for(int i=0;i<p.maximum;i++)
        {
            if(this->v[i] != p.v[i] && ( (this->v[i]>p.v[i] && this->v[i]-0.000001 > p.v[i]) || (this->v[i]<p.v[i] && this->v[i]+0.000001 < p.v[i]) ) )
            {
                return true;
            }
        }
    }

    return false;
}

CPolynomial& CPolynomial::operator=(const CPolynomial& p) {
    if(this != &p) {
        for (int i = 0; i < p.maximum; i++) {
            this->v[i] = p.v[i];
        }
        for(int i=p.maximum;i>=0;i--)
        {
            if(this->v[i] != 0)
            {
                this->maximum=i+1;
                break;
            }
            else if(i==0)
            {
                this->maximum=1;
            }
        }
    }
    return (*this);
}

#ifndef __PROGTEST__
bool smallDiff( double a, double b )
{
    // DIY
    if(a==b)
    {
        return true;
    }
    return false;
}

bool dumpMatch( const CPolynomial & x, const vector<double> & ref )
{
    // DIY
    for(unsigned int i=0;i<ref.size();i++)
    {
        if(ref[i] != x.v[i])
        {
            return false;
        }
    }
    return true;
}

int  main ( void )
{
    CPolynomial a, b, c;
    ostringstream out;
    a[0] = -10;
    a[1] = 3.5;
    a[3] = 1;

    assert ( smallDiff ( a ( 2 ), 5 ) );
    out . str ("");
    out << a;
    assert ( out . str () == "x^3 + 3.5*x^1 - 10" );
    a = a * -2;
    assert ( a . Degree () == 3 && dumpMatch ( a, vector<double>{ 20.0, -7.0, -0.0, -2.0 } ) );

    out . str ("");
    out << a;
    assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" );
    out . str ("");
    out << b;
    assert ( out . str () == "0" );
    b[5] = -1;
    out . str ("");
    out << b;
    assert ( out . str () == "- x^5" );
    c = a + b;
    assert ( c . Degree () == 5
             && dumpMatch ( c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );

    out . str ("");
    out << c;
    assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a - b;
    assert ( c . Degree () == 5
             && dumpMatch ( c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );

    out . str ("");
    out << c;
    assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a * b;
    assert ( c . Degree () == 8
             && dumpMatch ( c, vector<double>{ 0.0, -0.0, 0.0, -0.0, -0.0, -20.0, 7.0, 0.0, 2.0 } ) );

    out . str ("");
    out << c;
    assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
    assert ( a != b );
    b[5] = 0;
    assert ( !(a == b) );
    a = a * 0;
    assert ( a . Degree () == 0
             && dumpMatch ( a, vector<double>{ 0.0 } ) );

    assert ( a == b );

    // bonus
//    a[2] = 4;
//    a[1] = -3;
//    b[3] = 7;
//    out . str ("");
//    out << polynomial_variable ( "y" ) << "a=" << a << ", b=" << b;
//    assert ( out . str () == "a=4*y^2 - 3*y^1, b=7*y^3" );
//
//    out . str ("");
//    out << polynomial_variable ( "test" ) << c;
//    assert ( out . str () == "2*test^8 + 7*test^6 - 20*test^5" );
    return 0;
    /*Pavel Jahoda*/
}
#endif /* __PROGTEST__ */
