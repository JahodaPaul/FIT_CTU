#include <bits/stdc++.h>

using namespace std;
//NODE IS REPRESENTED BY POINT(X,Y coordinates), every point can connect
// what is the minimal cost to connect every node (minimal spanning tree)
vector<pair<double ,double >> xy;
int T,n;
double x,y;
int visited[101];
//connected node, price
vector<vector<pair<int,double>>> graph;

double length(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main() {
    cin>>T;
    while(T--)
    {
        memset(visited,0,sizeof(visited));
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>x>>y;
            xy.push_back(make_pair(x,y));
            vector<pair<int,double>> vector1;
            graph.push_back(vector1);
        }

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i!=j)
                {
                    double len = length(xy[i].first,xy[i].second,xy[j].first,xy[j].second);
                    graph[i].push_back(make_pair(j,len));
                }
            }
        }
        //price, connected node
        priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> q;
        q.push(make_pair(0.0,0));
        double result = 0;

        while(!q.empty())
        {
            pair<double,int> top = q.top();
            q.pop();
            if(!visited[top.second]) {
                result += top.first;
                for (int i = 0; i < graph[top.second].size(); i++) {
                    if(!visited[graph[top.second][i].first]) {
                        q.push(make_pair(graph[top.second][i].second, graph[top.second][i].first));
                    }
                }
                visited[top.second] = 1;
            }
        }
        cout << setprecision (2) << fixed << result << endl;
        if(T!=0) {
            cout << endl;
        }
        graph.clear();
        xy.clear();
    }

    return 0;
}
