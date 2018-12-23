#include <bits/stdc++.h>

using namespace std;

string arr[10];
string st;

int main() {
    arr[0] = "+---+|   ||   |+   +|   ||   |+---+";
    arr[1] = "    +    |    |    +    |    |    +";
    arr[2] = "+---+    |    |+---+|    |    +---+";
    arr[3] = "+---+    |    |+---+    |    |+---+";
    arr[4] = "+   +|   ||   |+---+    |    |    +";
    arr[5] = "+---+|    |    +---+    |    |+---+";
    arr[6] = "+---+|    |    +---+|   ||   |+---+";
    arr[7] = "+---+    |    |    +    |    |    +";
    arr[8] = "+---+|   ||   |+---+|   ||   |+---+";
    arr[9] = "+---+|   ||   |+---+    |    |+---+";

    while(1){
        vector<int> v;
        cin>>st;
        if(st == "end"){
            cout << "end" << endl;
            return 0;
        }
        for(int i=0;i<5;i++){
            if(i == 2){
                continue;
            }
            v.push_back(st[i]-'0');
        }
        for(int i=0;i<7;i++) {
            for (int k=0;k<4;k++) {
                for(int j=0;j<5;j++) {
                    cout << arr[v[k]][i*5+j];
                }
                if(k==0 || k==2){
                    cout << "  ";
                }
                else if(k==1){
                    if(i == 2 || i == 4){
                        cout << "  o  ";
                    }
                    else {
                        cout << "     ";
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }

    return 0;
}