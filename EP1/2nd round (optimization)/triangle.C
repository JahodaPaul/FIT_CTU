#include <bits/stdc++.h>

using namespace std;
int n;
int maxx = 0;

char arr[100][300];

int dpTableUpwards[100][300];
int dpTableDownwards[100][300];
int precomputed[10000];

int dpUpwards(int i, int j){
    if(i < 0 || j < 0 || i>=n || j>=(n+n-1) || arr[i][j] == '#'){
        return 0;
    }
    if(dpTableUpwards[i][j] != 0){ return dpTableUpwards[i][j]; }
    int res = 10000000;
    for(int k=0;k<3;k++){
        res = min(res,dpUpwards(i-1,j-1+k));
    }
    res = precomputed[res];
    dpTableUpwards[i][j] = res;
    return dpTableUpwards[i][j];
}

int dpDownWards(int i, int j){
    if(i < 0 || j < 0 || i>=n || j>=(n+n-1) || arr[i][j] == '#'){
        return 0;
    }
    if(dpTableDownwards[i][j] != 0){ return dpTableDownwards[i][j]; }
    int res = 10000000;
    for(int k=0;k<3;k++){
        res = min(res,dpDownWards(i+1,j-1+k));
    }
    res = precomputed[res];
    dpTableDownwards[i][j] = res;
    return dpTableDownwards[i][j];
}

void CheckTriangles(){
    int tmp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n+n-1;j++){
            tmp = dpUpwards(i,j);
            tmp = dpDownWards(i,j);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n+n-1;j++){
            if(i%2==1 && j%2==0 && dpTableUpwards[i][j] > 1){
                dpTableUpwards[i][j] = 1;
            }
            else if(i%2==0 && j%2==1 && dpTableUpwards[i][j] > 1){
                dpTableUpwards[i][j] = 1;
            }
            maxx = max(dpTableUpwards[i][j],maxx);
            if(i%2==0 && j%2==0 && dpTableDownwards[i][j] > 1){
                dpTableDownwards[i][j] = 1;
            }
            else if(i%2==1 && j%2==1 && dpTableDownwards[i][j] > 1){
                dpTableDownwards[i][j] = 1;
            }
            maxx = max(dpTableDownwards[i][j],maxx);
        }
    }
}

int main() {
    int howMany = 1;
    int res = 0;
    precomputed[0] = 1;
    for(int i=0;i<100;i++){
        precomputed[res] = res+howMany;
        res += howMany;
        howMany += 2;
    }

    ios::sync_with_stdio(0);
    int counter = 0;
    while(1){
        counter++;
        maxx = 0;
        cin>>n;
        if(n==0){
            return 0;
        }
        memset(dpTableUpwards,0,sizeof(dpTableUpwards));
        memset(dpTableDownwards,0,sizeof(dpTableDownwards));
        memset(arr,'#',sizeof(arr));
        string st;
        for(int i=0;i<n;i++){
            cin>>st;
            for(int j=0;j<st.length();j++){
                arr[i][j+i] = st[j];
            }
        }
        CheckTriangles();
        cout << "Triangle #" << counter<< endl;
        cout << "The largest triangle area is " << maxx << "." << endl;
        cout << endl;
    }
}