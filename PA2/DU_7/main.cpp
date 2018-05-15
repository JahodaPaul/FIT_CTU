#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST_ */

class Predmet
{
public:
    virtual int Weight() = 0;
    virtual bool AreYouDangerous()  = 0;
    virtual string ToString(string s) = 0;
    virtual Predmet* clone() const=0;
    virtual ~Predmet(){};
};

class CKnife: public Predmet
{
public:
    CKnife (int bladeLength ){lenght=bladeLength;};
    virtual Predmet* clone() const{CKnife *k=new CKnife(lenght);return k;};
    virtual int Weight(){return 100;};
    virtual bool AreYouDangerous(){if(lenght>7){return true;}else{return false;}}
    virtual string ToString(string s){string res ="";
        res+=s;res+="Knife, blade: ";
        stringstream ss;
        ss << lenght;string str = ss.str();
        res+= str;res+=" cm\n";
        return res;
        }
    int lenght;
};

class CClothes:public Predmet
{
public:
    CClothes (string desc ){what=desc;};
    virtual Predmet* clone() const{CClothes *k=new CClothes(what);return k;};
    virtual bool AreYouDangerous(){return false;}
    virtual int Weight(){return 500;}
    virtual string ToString(string s){return s + "Clothes ("+what+")\n";}

    string what;
};

class CShoes:public Predmet
{
public:
    CShoes (){};
    virtual Predmet* clone() const{Predmet *k=new CShoes();return k;};
    virtual int Weight(){return 750;}
    virtual bool AreYouDangerous() {return false;}
    virtual string ToString(string s){return s + "Shoes\n";}
};

class CMobile:public Predmet
{
public:
    CMobile ( string manufacturer,string model ){mod=model;fromwho=manufacturer;};
    virtual Predmet* clone() const{CMobile *k=new CMobile(fromwho,mod);return k;};
    virtual bool AreYouDangerous(){if(mod=="Galaxy Note S7" && fromwho=="Samsung"){return true;}else{return false;}}
    virtual int Weight(){return 150;};
    virtual string ToString(string s){return s + "Mobile "+mod+" by: "+fromwho+"\n";}

    string mod,fromwho;
};

class Container
{
public:
    Container(int containerWeight){ weight = containerWeight;};
    template <class T>
    Container& Add(const T& predmet){v.push_back(predmet.clone());return *this;}
    int Weight() const{
        int result=0;
        result+=weight;
        for(unsigned int i=0;i<v.size();i++)
        {
            result+=v[i]->Weight();
        }
        return result;
    };
    int Count() const{return v.size();};
    bool Danger() const{
        bool b=false;
        for(unsigned int i=0;i<v.size();i++)
        {
            if(v[i]->AreYouDangerous())
            {
                b=true;
                break;
            }
        }
        return b;
    };
    bool IdenticalContents(const Container& c) const{
        if(v.size()!=c.v.size())
        {return false;}
        for(unsigned int i=0;i<v.size();i++)
        {
            bool b=false;
            string s=v[i]->ToString("");
            for(unsigned int j=0;j<c.v.size();j++)
            {
                string s2=c.v[j]->ToString("");
                if(s==s2)
                {
                    b=true;
                    break;
                }
            }
            if(!b)
            {
                return false;
            }
        }
        return true;
    };
    virtual string ToString() const = 0;
    friend ostream &operator<<(ostream& o,const Container & p){
        o << p.ToString();
        unsigned int nOfV=p.v.size();
        for(unsigned int i=0;i<nOfV;i++)
        {
            string s;
            if(i!=(nOfV-1))
            {
                s="+-";
            } else{
                s="\\-";
            }
            o << p.v[i]->ToString(s);
        }
        return o;
    }
    virtual ~Container(){
        for(unsigned int i=0;i<v.size();i++)
        {
            delete v[i];
        }
        v.clear();
    };
protected:
    vector<Predmet*> v;
    int weight;
};

class CSuitcase : public Container
{
public:
    CSuitcase ( int w,int h, int d ):Container(2000)
    {
        this->w=w;this->h=h;this->d=d;
    }
    CSuitcase (const CSuitcase & cSuitcase):CSuitcase(w,h,d)
    {
        (*this)=cSuitcase;
    }
    CSuitcase& operator =(const CSuitcase & cSuitcase)
    {
        if(this!=&cSuitcase)
        {
            if(this->v.size())
            {
                for(unsigned int i=0;i<v.size();i++)
                {
                    delete v[i];
                }
                v.clear();
            }
            this->Container::weight=2000;
            this->w=cSuitcase.w;
            this->d=cSuitcase.d;
            this->h=cSuitcase.h;
            for(unsigned int i=0;i<cSuitcase.v.size();i++)
            {
                this->v.push_back(cSuitcase.v[i]->clone());
            }
        }
        return (*this);
    }
    virtual string ToString() const{
        string res="";
        res+="Suitcase ";
        stringstream ss;
        ss << w;string str = ss.str();
        stringstream sss;
        res+=(str+"x");
        sss << h;str = sss.str();
        stringstream ssss;
        res+=(str+"x");
        ssss << d;str = ssss.str();
        res+=(str+"\n");
        return res;
        };
protected:
    int w,h,d;
};

class CBackpack: public Container
{
public:
    CBackpack():Container(1000){};
    CBackpack(const CBackpack & cBackpack):CBackpack()
    {
        (*this)=cBackpack;
    }
    CBackpack& operator =(const CBackpack & cBackpack)
    {
        if(this!=&cBackpack)
        {
            if(this->v.size())
            {
                for(unsigned int i=0;i<v.size();i++)
                {
                    delete v[i];
                }
                v.clear();
            }
            this->Container::weight=1000;
            for(unsigned int i=0;i<cBackpack.v.size();i++)
            {
                this->v.push_back(cBackpack.v[i]->clone());
            }
        }
        return (*this);
    }
    virtual string ToString() const{return "Backpack\n";}
};

#ifndef __PROGTEST__
int main ( void )
{
    CSuitcase x ( 1, 2, 3 );
    CBackpack y;
    ostringstream os;
    x . Add ( CKnife ( 7 ) );
    x . Add ( CClothes ( "red T-shirt" ) );
    x . Add ( CClothes ( "black hat" ) );
    x . Add ( CShoes () );
    x . Add ( CClothes ( "green pants" ) );
    x . Add ( CClothes ( "blue jeans" ) );
    x . Add ( CMobile ( "Samsung", "J3" ) );
    x . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
    os . str ( "" );
    os << x;
    assert ( os . str () == "Suitcase 1x2x3\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Clothes (black hat)\n"
            "+-Shoes\n"
            "+-Clothes (green pants)\n"
            "+-Clothes (blue jeans)\n"
            "+-Mobile J3 by: Samsung\n"
            "\\-Mobile Galaxy Note S7 by: Tamtung\n" );
    assert ( x . Count () == 8 );
    assert ( x . Weight () == 5150 );
    assert ( !x . Danger () );
    x . Add ( CKnife ( 8 ) );
    os . str ( "" );
    os << x;
    assert ( os . str () == "Suitcase 1x2x3\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Clothes (black hat)\n"
            "+-Shoes\n"
            "+-Clothes (green pants)\n"
            "+-Clothes (blue jeans)\n"
            "+-Mobile J3 by: Samsung\n"
            "+-Mobile Galaxy Note S7 by: Tamtung\n"
            "\\-Knife, blade: 8 cm\n" );
    assert ( x . Count () == 9 );
    assert ( x . Weight () == 5250 );
    assert ( x . Danger () );
    y . Add ( CKnife ( 7 ) )
            . Add ( CClothes ( "red T-shirt" ) )
            . Add ( CShoes () );
    y . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
    y . Add ( CShoes () );
    y . Add ( CClothes ( "blue jeans" ) );
    y . Add ( CClothes ( "black hat" ) );
    y . Add ( CClothes ( "green pants" ) );
    os . str ( "" );
    os << y;
    assert ( os . str () == "Backpack\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Shoes\n"
            "+-Mobile Galaxy Note S7 by: Samsung\n"
            "+-Shoes\n"
            "+-Clothes (blue jeans)\n"
            "+-Clothes (black hat)\n"
            "\\-Clothes (green pants)\n" );
    assert ( y . Count () == 8 );
    assert ( y . Weight () == 4750 );
    assert ( y . Danger () );
    y . Add ( CMobile ( "Samsung", "J3" ) );
    y . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
    y . Add ( CKnife ( 8 ) );
    os . str ( "" );
    os << y;
    assert ( os . str () == "Backpack\n"
            "+-Knife, blade: 7 cm\n"
            "+-Clothes (red T-shirt)\n"
            "+-Shoes\n"
            "+-Mobile Galaxy Note S7 by: Samsung\n"
            "+-Shoes\n"
            "+-Clothes (blue jeans)\n"
            "+-Clothes (black hat)\n"
            "+-Clothes (green pants)\n"
            "+-Mobile J3 by: Samsung\n"
            "+-Mobile Galaxy Note S7 by: Tamtung\n"
            "\\-Knife, blade: 8 cm\n" );
    assert ( y . Count () == 11 );
    assert ( y . Weight () == 5150 );
    assert ( y . Danger () );
    assert ( !x . IdenticalContents ( y ) );
    assert ( !y . IdenticalContents ( x ) );
    x . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
    assert ( !x . IdenticalContents ( y ) );
    assert ( !y . IdenticalContents ( x ) );
    x . Add ( CShoes () );
    assert ( x . IdenticalContents ( y ) );
    assert ( y . IdenticalContents ( x ) );
    assert ( y . IdenticalContents ( y ) );
    assert ( x . IdenticalContents ( x ) );
    return 0;
    /*Pavel Jahoda*/
}
#endif /* __PROGTEST__ */
