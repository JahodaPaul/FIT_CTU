#include <bits/stdc++.h>

using namespace std;

vector<char> arr;

int TranslatePolishIntoInfix(int index){
    if(index >= arr.size()){
        return 100000000;
    }
    if(arr[index] - '0' >= 0 && arr[index] - '0' <= 9){
        cout << arr[index] << " ";
        return index + 1;
    }
    int tmp = TranslatePolishIntoInfix(index+1);
    int tmp2 = TranslatePolishIntoInfix(tmp);
    cout << arr[index] << " ";
    return tmp2;
}

int main() {
    string st;
    while(1){
        arr.clear();
        getline (std::cin,st);
        if(st=="0"){return 0;}
        for(int i=0;i<st.length();i++){
            if(i%2==0){
                arr.push_back(st[i]);
            }
        }
        TranslatePolishIntoInfix(0);
        cout << endl;
    }
}