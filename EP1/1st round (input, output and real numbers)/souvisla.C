#include <bits/stdc++.h>
#define ll long long int

using namespace std;

ll t;

int main() {
    ios::sync_with_stdio(0);
    cin>>t;
    for(ll i=0;i<t;i++){
        ll prev = -2;
        ll now;
        ll max = 0;
        ll nowCounter = 0;
        while(1){
            cin>>now;
            if(now==0){
                if(nowCounter > max){
                    max = nowCounter;
                }
                break;
            }
            if(now>=prev){
                nowCounter += 1;
            }
            else{
                if(nowCounter > max){
                    max = nowCounter;
                }
                nowCounter = 1;
            }
            prev = now;
        }
        cout << max << endl;
    }
    return 0;
}