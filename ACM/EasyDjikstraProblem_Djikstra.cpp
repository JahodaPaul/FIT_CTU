#include <bits/stdc++.h>

//DIRECTED GRAPH DJIKSTRA FINDING PATH, IF NOT FOUND PRINT "NO"

using namespace std;
int nodes[10001];
int T,nOfVertices,nOfEdges;
int visited[10001];
//connected node, cost
vector<vector<pair<int,int>>> graph;

int main() {
    cin >> T;
    int a,b,cost,start,end;
    while(T--){
        //cost, connected node
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int> >> prior_q;
        memset(nodes,63,sizeof(nodes));
        memset(visited,0,sizeof(visited));
        cin >> nOfVertices;
        cin >> nOfEdges;
        for(int i=0;i<=nOfVertices;i++){
            vector<pair<int,int>> v;
            graph.push_back(v);
        }
        for(int i=0;i<nOfEdges;i++){
            cin >> a;
            cin >> b;
            cin >> cost;
            graph[a].push_back(make_pair(b,cost));
        }
        cin >> start;
        cin >> end;
        prior_q.push(make_pair(0,start));
        nodes[start] = 0;
        while(!prior_q.empty())
        {
            int currentNode = prior_q.top().second;
            for(int i=0;i<graph[currentNode].size();i++){
                int newNode = graph[currentNode][i].first;
                int vertexCost = graph[currentNode][i].second;
                if(nodes[currentNode] + vertexCost < nodes[newNode] ) {
                    int lengthFromStart = nodes[currentNode] + vertexCost;
                    nodes[newNode] = lengthFromStart;
                    prior_q.push(make_pair(lengthFromStart, newNode  ) );
                }
            }
            visited[currentNode] = 1;
            prior_q.pop();
        }
        if(!visited[end]){
            cout << "NO" << endl;
        }
        else{
            cout << nodes[end] << endl;
        }
        graph.clear();
    }
    return 0;
}