#include <bits/stdc++.h>

using namespace std;

//before, taken or not
int dpTable[1001][2];
vector<vector<int>> graph;

int n;

int dp(int indexBefore,int indexNow, int takenOrNot)
{
    if(graph[indexNow].size() == 1 && graph[indexNow][0] == indexBefore){
        return 0;
    }

    if(dpTable[indexNow][takenOrNot] != 1061109567) return dpTable[indexNow][takenOrNot];

    if(!takenOrNot){
        int suma = 0;
        for(int i=0;i<graph[indexNow].size();i++){
            if(graph[indexNow][i] != indexBefore)
            suma += (dp(indexNow,graph[indexNow][i],1)+1);
        }
        dpTable[indexNow][takenOrNot] = suma;
    }
    else{
        int suma = 0;
        for(int i=0;i<graph[indexNow].size();i++){
            if(graph[indexNow][i] != indexBefore)
            suma += min(dp(indexNow,graph[indexNow][i],1)+1,dp(indexNow,graph[indexNow][i],0));
        }
        dpTable[indexNow][takenOrNot] = suma;
    }
    return dpTable[indexNow][takenOrNot];
}

inline int read() {
    register int c=getchar();int x=0;
    for(;c<48||c>57;c=getchar());
    for(;c>47&&c<58;c=getchar())
        x=(x<<1)+(x<<3)+c-48;
    return x;
}

int main() {
    for(int i=0;i<=1001;i++)
    {
        graph.push_back(vector<int>());
    }
    while(cin>>n){
        if(!n){return 0;}
        memset(dpTable,63,sizeof(dpTable));

        int tmp,value;
        for(int i=0;i<n;i++){
            tmp=read();
            for(int j=0;j<tmp;j++){
                value=read();
                graph[i+1].push_back(value);
            }
        }
        if(n==1){cout << "1" << endl;
            graph[1].clear();continue;}
        int resTaken = dp(-1,1,1)+1;
        int resNotTaken = dp(-1,1,0);

        int result = min(resTaken,resNotTaken);
        cout << result << endl;
        //clear
        for(int i=1;i<=n;i++){
            graph[i].clear();
        }
    }
    return 0;
}
