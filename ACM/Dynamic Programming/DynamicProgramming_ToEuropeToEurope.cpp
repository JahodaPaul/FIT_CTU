#include <bits/stdc++.h>

using namespace std;

int bridgeSustain,bridgeLength,n;
int weights[1001],speeds[1001];

double dpTable[1001][1001];

double dp(int lastIndexGroupDivide, int currentIndex,int weightLeft, int slowestInGroup){
    if(currentIndex >= n){
        return bridgeLength/(double)slowestInGroup;
    }
    if(dpTable[lastIndexGroupDivide][weightLeft] != 0){return dpTable[lastIndexGroupDivide][weightLeft];}
    if(weightLeft - weights[currentIndex] < 0){
        dpTable[lastIndexGroupDivide][weightLeft] = dp(currentIndex,currentIndex+1,bridgeSustain-weights[currentIndex],speeds[currentIndex]) +
                                                    bridgeLength/(double)slowestInGroup;
    }
    else{
        int futureSlowest = speeds[currentIndex] < slowestInGroup? speeds[currentIndex] : slowestInGroup;
        dpTable[lastIndexGroupDivide][weightLeft] = min(dp(currentIndex,currentIndex+1,bridgeSustain-weights[currentIndex],speeds[currentIndex]) +
                                                        bridgeLength/(double)slowestInGroup,
                                                        dp(lastIndexGroupDivide,currentIndex+1,weightLeft-weights[currentIndex],futureSlowest));
    }
    return dpTable[lastIndexGroupDivide][weightLeft];
}

int main() {
    while(cin>>bridgeSustain>>bridgeLength>>n){
        if(!bridgeSustain && !bridgeLength && !n){
            return 0;
        }

        memset(dpTable,0,sizeof(dpTable));
        for(int i=0;i<n;i++){
            cin>>weights[i]>>speeds[i];
        }
        double result = dp(0,1,bridgeSustain-weights[0],speeds[0]);
        cout << setprecision(1) << fixed << (result*60) << endl;
    }
}