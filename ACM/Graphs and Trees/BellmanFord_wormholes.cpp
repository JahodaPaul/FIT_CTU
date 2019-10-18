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

int main() {
    int a,b,cost;
    ios::sync_with_stdio(0);
    cin >> T;
    while(T--){
        memset(arr,63,sizeof(arr));
        cin>>nOfVertices>>nOfEdges;
        for(int i =0;i<=nOfVertices;i++){
            vector<pair<int,int>> vector1;
            graph.push_back(vector1);
        }

        for(int i=0;i<nOfEdges;i++){
            cin>>a>>b>>cost;
            graph[a].push_back(make_pair(b,cost));
        }

        bool b = false;
        arr[0] = 0;
        for(int i=0;i<nOfVertices;i++){
            for(int j=0;j<nOfVertices;j++){
                for(int k=0;k<graph[j].size();k++){
                    if(graph[j][k].second + arr[j] < arr[graph[j][k].first]){
                        arr[graph[j][k].first] = graph[j][k].second + arr[j];
                    }
                }
            }
        }

        for(int j=0;j<nOfVertices;j++){
            for(int k=0;k<graph[j].size();k++){
                if(graph[j][k].second + arr[j] < arr[graph[j][k].first]){
                    b = true;
                }
            }
        }


        if(b){
            cout << "possible" << endl;
        }
        if(!b){
            cout << "not possible" << endl;
        }

        graph.clear();
    }
    return 0;
}
