#include <bits/stdc++.h>

using namespace std;

char arr[512][512];
int n;
string st;

char hexa[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

int in;

void recursion(int index, int number,int x, int y){
    if(st[index] == 'B' || st[index] == 'W'){
        for(int i=x;i<x+number;i++){
            for(int j=y;j<y+number;j++){
                arr[j][i] = st[index];
            }
        }
        in = index + 1;
        return;
    }
    number = number/2;
    recursion(index+1,number,x,y);
    recursion(in,number,x+number,y);
    recursion(in,number,x,y+number);
    recursion(in,number,x+number,y+number);
}

void calculateHexaAndOutputIt(){
    int numberOfHexas = n/8;
    for(int i=0;i<n;i++){
        for(int j=0;j<numberOfHexas;j++){
            int decimal = 0;
            int tmp = 1;
            for(int k=0;k<8;k++){
                if(arr[i][j*8+k] == 'B'){
                    decimal += tmp;
                }
                tmp *= 2;
            }
            cout << "0x" << hexa[decimal/16] << hexa[decimal%16] << ",";
        }
        cout << endl;
    }
}

int main() {
    cin>>n;
    cin>>st;
    cout << "#define quadtree_width " << n << endl;
    cout << "#define quadtree_height " << n << endl;
    cout << "static char quadtree_bits() = {" << endl;
    recursion(0,n,0,0);
    calculateHexaAndOutputIt();
    cout << "};" << endl;
    return 0;
}
