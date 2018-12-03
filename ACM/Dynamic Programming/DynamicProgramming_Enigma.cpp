#include <bits/stdc++.h>

using namespace std;

string dpTable[1001][1001];

string st;

int factor;

string dp(int index, int remainder){
    if(index >= st.size()){
        if(remainder == 0){
            return "";
        }
        else{
            return "-1";
        }
    }
    if(dpTable[index][remainder] != "-2"){return dpTable[index][remainder];}
    if(st[index] == '?'){
        int i = (index==0)?1:0;
        for(i;i<10;i++){
            string tmp = dp(index+1,(remainder*10+i)%factor);
            if(tmp == "-1"){
                dpTable[index][remainder] = tmp;
            }
            else{
                dpTable[index][remainder] = string(1, (char)(i+'0')) + tmp;
                break;
            }
        }
    }
    else{
        string tmp = dp(index+1,(remainder*10+(st[index]-'0'))%factor);
        if(tmp == "-1"){
            dpTable[index][remainder] = tmp;
        }
        else{
            dpTable[index][remainder] = string(1, st[index]) + tmp;
        }
    }
    return dpTable[index][remainder];
}

int main() {
    for(int i=0;i<1001;i++){
        for(int j=0;j<1001;j++){
            dpTable[i][j] = "-2";
        }
    }
    cin>>st>>factor;
    string res = dp(0,0);
    if(res == "-1"){
        cout << "*" << endl;
    }
    else{
        cout << res << endl;
    }

    return 0;
}