#include <bits/stdc++.h>

//Input
//The input file starts with a line containing the number of cases c to be analysed. Each case starts with
//a line with two numbers n and m. These indicate the number of star systems (1 ≤ n ≤ 1000) and
//the number of wormholes (0 ≤ m ≤ 2000). The star systems are numbered from 0 (our solar system)
//through n − 1 . For each wormhole a line containing three integer numbers x, y and t is given. These
//numbers indicate that this wormhole allows someone to travel from the star system numbered x to the
//star system numbered y, thereby ending up t (−1000 ≤ t ≤ 1000) years in the future.
//Output
//The output consists of c lines, one line for each case, containing the word ‘possible’ if it is indeed
//possible to go back in time indefinitely, or ‘not possible’ if this is not possible with the given set of
//star systems and wormholes

using namespace std;
//kam, cena
vector<vector<pair<int,int>>> graph;
int T,nOfEdges,nOfVertices;
int arr[1002];
int arr2[1002];

int main() {
    int a,b,cost;
    ios::sync_with_stdio(0);
    cin >> T;
    while(T--){
        memset(arr,63,sizeof(arr));
        memset(arr2,63,sizeof(arr2));
        cin>>nOfVertices>>nOfEdges;
        int kMinusOne = nOfVertices-1,k = nOfVertices;
        for(int i =0;i<=nOfVertices;i++){
            vector<pair<int,int>> vector1;
            graph.push_back(vector1);
        }

        for(int i=0;i<nOfEdges;i++){
            cin>>a>>b>>cost;
            graph[a].push_back(make_pair(b,cost));
        }
        //cena, kam, round
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> q;
        q.push(make_pair(0,make_pair(0,0)));
        arr[0] = 0;
        while(!q.empty()){
            pair<int,pair<int,int>> q2 = q.top();
            q.pop();
            for(int i=0;i<graph[q2.second.first].size();i++){
                int length = arr[q2.second.first] + graph[q2.second.first][i].second;
                if(length < arr[graph[q2.second.first][i].first] && q2.second.second < kMinusOne)
                {
                    arr[graph[q2.second.first][i].first] = length;
                    q.push(make_pair(length,make_pair(graph[q2.second.first][i].first,q2.second.second+1)));
                }
            }

        }
        while(!q.empty()){q.pop();}
        q.push(make_pair(0,make_pair(0,0)));
        arr2[0] = 0;
        while(!q.empty()){
            pair<int,pair<int,int>> q2 = q.top();
            q.pop();
            for(int i=0;i<graph[q2.second.first].size();i++){
                int length = arr2[q2.second.first] + graph[q2.second.first][i].second;
                if(length < arr2[graph[q2.second.first][i].first] && q2.second.second < k)
                {
                    arr2[graph[q2.second.first][i].first] = length;
                    q.push(make_pair(length,make_pair(graph[q2.second.first][i].first,q2.second.second+1)));
                }
            }
        }
        bool b = false;
        for(int i=0;i<1001;i++){
            if(arr[i] != arr2[i]){
                cout << "possible" << endl;
                b = true;
                break;
            }
        }
        if(!b){
            cout << "not possible" << endl;
        }

        graph.clear();
    }
    return 0;
}
