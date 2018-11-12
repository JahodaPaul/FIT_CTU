#include <bits/stdc++.h>

using namespace std;
int collected[1000005];
vector<vector<int>> graph;

int n,k;

int main() {
    ios::sync_with_stdio(0);

    while(cin>>n>>k) {
        memset(collected,0,sizeof(collected));
        graph.clear();
        graph.resize(2000005);
        int size,tmp;
        for (int i = 0; i < n;i++)
        {
            cin>>size;
            for(int j=0;j<size;j++) {
                cin >> tmp;
                graph[i].push_back(tmp);
                graph[i + n].push_back(tmp);
            }
        }

        int start = 0, end = 0;
        int nOfBrands = 0;
        int min = -1;
        int res = 0;
        while(end<2*n){
            while(nOfBrands != k){
                for(int i=0;i<graph[end].size();i++){
                    if(collected[graph[end][i]] == 0){
                        nOfBrands += 1;
                    }
                    collected[graph[end][i]] += 1;
                    res += 1;
                }
                end += 1;
                if(end>=2*n){
                    break;
                }
            }
            while(nOfBrands == k){
                if( (min == -1 && k==nOfBrands) || (k == nOfBrands && res < min) ){
                    min = res;
                }
                for(int i=0;i<graph[start].size();i++){
                    if(collected[graph[start][i]] == 1){
                        nOfBrands -= 1;
                    }
                    collected[graph[start][i]] -= 1;
                    res -= 1;
                }
                start += 1;
            }
        }
        cout << min << endl;

    }
    return 0;
}
