#include <bits/stdc++.h>

using namespace std;

int dpTable[10000];

int values[501],weight[501];

int targetWeight;

int t,n;

int dp(int currentWeight){
    if(currentWeight == targetWeight){
        return 0;
    }
    if(currentWeight > targetWeight){
        return -1;
    }
    if(dpTable[currentWeight] != 0){return dpTable[currentWeight];}

    int res = -1;
    for(int i=0;i<n;i++){
        int tmp = dp(currentWeight+weight[i]);
        if(tmp != -1 &&  (tmp+values[i] <res || res == -1)){
            res = tmp+values[i];
        }
    }
    dpTable[currentWeight] = res;
    return dpTable[currentWeight];
}

int main() {
    cin>>t;
    while(t--){
        memset(dpTable,0,sizeof(dpTable));
        int e,f;
        cin>>e>>f;
        targetWeight = f-e;

        cin>>n;
        int l,k;
        for(int i=0;i<n;i++){
            cin>>l>>k;
            values[i] = l;
            weight[i] = k;
        }

        if(!targetWeight){
            cout << "The minimum amount of money in the piggy-bank is 0." << endl;
        }
        else{
            int res = dp(0);
            if(res == -1){
                cout << "This is impossible." << endl;
            }
            else{
                cout << "The minimum amount of money in the piggy-bank is " << res << "." << endl;
            }
        }
    }

    return 0;
}