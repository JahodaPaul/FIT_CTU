#include <bits/stdc++.h>

using namespace std;

int n;
int arr[5000];
int dpTable[5000][2];

inline int read() {
    register int c=getchar();int x=0;
    for(;c<48||c>57;c=getchar());
    for(;c>47&&c<58;c=getchar())
        x=(x<<1)+(x<<3)+c-48;
    return x;
}

int main() {
    while(scanf("%d",&n) == 1){
        memset(dpTable,0,sizeof(dpTable));
        for(int i =0;i<n;i++){
            arr[i] = read();
        }

        for(int i=n-1;i>=0;i--){
            for(int j=i+1;j<n;j++){
                if(arr[i] == arr[j]){
                    dpTable[j][i%2] = dpTable[j-1][!(i%2)] + 1;
                }
                else{
                    dpTable[j][i%2] = max(dpTable[j][!(i%2)],dpTable[j-1][i%2]);
                }
            }
        }
        int tmp = 0;
        for(int i=0;i<n;i++){
            tmp = max(tmp,dpTable[i][0]);
            tmp = max(tmp,dpTable[i][1]);
        }
        printf("%d\n",tmp);

    }
    return 0;
}
