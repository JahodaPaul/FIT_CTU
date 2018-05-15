#include <iostream>
#include <stdio.h>
#include <sstream>

using namespace std;
int choice,b=1;
string st;

void IsNumber()
{
    for(unsigned int i=0;i<st.length();i++)
    {
        if((st[i]-'0' < 0) || (st[i]-'0' > 9)){
            b=0;
            i=st.length();
        }
    }
    if(b)
    {
        istringstream ss(st);
        ss >> choice;
    }
}

int main()
{
    cin >> st;
    IsNumber();
    if(b)
    {
        cout << "ml' nob:\n";
        if(choice<1 || choice > 5)
        {
            cout << "luj\n";
        }
        else{
            cout << "Qapla'\n";
            switch (choice)
            {
             case 1:
                cout << "noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n";
                break;
             case 2:
                cout << "Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n";
                break;
            case 3:
                cout << "qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n";
                break;
            case 4:
                cout << "Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n";
                break;
            case 5:
                cout << "leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n";
                break;
            }
        }
    }
    else{
        cout << "ml' nob:\n";
        cout << "luj\n";
    }
    return 0;
/*Pavel Jahoda*/
}
