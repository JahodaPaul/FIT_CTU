#include <bits/stdc++.h>

using namespace std;

vector<int> howManyPointToIt;
vector<vector<int>> graph;
int done[101];

int nOfVertices,nOfEdges;

bool Done(int maximum){
    for(int i = 1;i<=maximum;i++){
        if(done[i] != 1){
            return false;
        }
    }
    return true;
}

int main() {
    int a,b;
    while(cin>>nOfVertices>>nOfEdges){
        memset(done,0,sizeof(done));
        if(nOfVertices == 0 && nOfEdges == 0){
            return 0;
        }
        graph.resize(nOfVertices+1,vector<int>());
        howManyPointToIt.resize(nOfVertices+1,0);
        for(int i=0;i<nOfEdges;i++){
            cin>>a>>b;
            graph[a].push_back(b);
            howManyPointToIt[b] += 1;
        }

        deque<int> q;
        while(!Done(nOfVertices)){
            int tmp = (int)howManyPointToIt.size();
            for(int i=tmp-1;i>=0;i--){
                if(howManyPointToIt[i] == 0 && i!= 0 && !done[i]){
                    q.push_back(i);
                    cout << i << " ";
                    done[i] = 1;
                }
            }
            while(!q.empty()){
                int tmp = graph[q.front()].size();
                for(int i=0;i<tmp;i++){
                    howManyPointToIt[graph[q.front()].back()] -= 1;
                    graph[q.front()].pop_back();
                }
                q.pop_front();
            }
        }
        cout << endl;

        howManyPointToIt.clear();
        graph.clear();
    }

    return 0;
}
