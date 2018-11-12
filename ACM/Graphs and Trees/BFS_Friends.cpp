#include <bits/stdc++.h>

using namespace std;

int n,m,l;
int visited[30005];

int main() {

    cin >> n;
    for(int i=0;i<n;i++){
        cin >> m;
        cin >> l;
        vector<vector<int>> v;
        v.resize(m+1,vector<int>());
        memset(visited,0,sizeof(visited));

        int o,p;
        for(int j=0;j<l;j++){
            cin>>o;cin>>p;
            bool found = false;
            for(int k=0;k<v[o].size();k++){
                if(v[o][k] == p){
                    found = true;
                    break;
                }
            }
            if(!found){
                v[o].push_back(p);
                v[p].push_back(o);
            }
        }
        int maximum = 0;
        int tmp = 0;
        deque<int> q;
        q.push_back(1);
        visited[1] = 1;

        while(!q.empty()) {
            tmp = 0;
            while (!q.empty()) {
                int temporary = int(v[q.front()].size());
                for (int j = 0; j < temporary; j++) {
                    if(!visited[v[q.front()][j]]) {
                        q.push_back(v[q.front()][j]);
                        visited[v[q.front()][j]] = 1;
                    }
                }
                q.pop_front();
                tmp++;
            }
            if(tmp > maximum){
                maximum = tmp;
            }

            for(int j=0;j<v.size();j++){
                if(!visited[j]){
                    q.push_back(j);
                    visited[j] = 1;
                    break;
                }
            }
        }
        std::cout << maximum << std::endl;
    }

    return 0;
}
