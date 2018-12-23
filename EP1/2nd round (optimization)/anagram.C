#include <bits/stdc++.h>

using namespace std;

char arr[8];
set<string> mySet;
int n;

void permutations(int index,string a){
    if(index==n){
        mySet.insert(a);
        return;
    }
    for(int i=0;i<n;i++){
        string tmp(a);
        if(tmp[i] == '-'){
            tmp[i] = arr[index];
            permutations(index+1,tmp);
        }
    }
}

int main() {
    string st;
    while(cin>>st){
        mySet.clear();
        string seed = "";
        for(int i=0;i<st.length();i++){
            arr[i] = st[i];
            seed+='-';
        }
        n=(int)st.length();
        permutations(0,seed);
        for(auto it = mySet.begin();it!=mySet.end();it++){
            cout << *it << endl;
        }
        cout << endl;
    }

    return 0;
}