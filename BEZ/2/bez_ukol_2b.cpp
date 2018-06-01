#include <bits/stdc++.h>
using namespace std;

map<char,int> mapa;
char pole[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

string sifra1,sifra2,ot1,ot2,s1,s2,heslo;

int main(int argc, char *argv[]){
    for(int i=0;i<16;i++){
        mapa.insert(make_pair(pole[i],i));
    }
    cin>>s1;
    cin>>s2;
    cin>>ot1;
    for(int i=0;i<s1.size();i+=2){
        sifra1 += (char)( (mapa.find(s1[i]))->second * 16 + (mapa.find(s1[i+1]))->second );
        sifra2 += (char)( (mapa.find(s2[i]))->second * 16 + (mapa.find(s2[i+1]))->second );
        heslo += (sifra1[i/2] ^ ot1[i/2] );
        ot2 += (heslo[i/2] ^ sifra2[i/2]);
    }
    cout << ot2 << endl;

}
