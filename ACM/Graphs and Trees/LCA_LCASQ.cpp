#include <bits/stdc++.h>

using namespace std;

struct node{
    int parent;
    int index;
    int depth;
    int nOfDescendants;
    vector<int> children;
    node(){
        depth = 0;
        nOfDescendants = 0;
    }
};



vector<int> paths; // heads
vector<node> nodes;

int nOfNodes,nOfChildren,nOfqueries,u,v,tmp_node;

int preorder(int index, int depth){
    nodes[index].depth = depth;

    for(int i=0;i<nodes[index].children.size();i++){
        int nOfDescendants = preorder(nodes[nodes[index].children[i]].index,depth+1);
        nodes[index].nOfDescendants += nOfDescendants;
    }

    return nodes[index].nOfDescendants + 1;
}

int main() {
    cin>>nOfNodes;

    for(int i=0;i<nOfNodes;i++) {
        nodes.push_back(node());
        paths.push_back(-1);
    }

    for(int i=0;i<nOfNodes;i++){
        nodes[i].index = i;
        cin>>nOfChildren;
        for(int j=0;j<nOfChildren;j++) {
            cin>>tmp_node;
            nodes[i].children.push_back(tmp_node);
            nodes[tmp_node].parent = i;
        }
    }

    // root of the tree is always 0, therefore we don't need to find it
    // create paths
    // BFS

    preorder(0,0);

    // pick the fattest one - the one with most descendants

    deque<int> q;
    q.push_back(0);
    paths[0] = 0;

    while(!q.empty()){
        int now = q.front();
        q.pop_front();
        int maximum = -1;
        int index = -1;
        for(int i=0;i<nodes[now].children.size();i++){
            q.push_back(nodes[now].children[i]);
            if (nodes[nodes[now].children[i]].nOfDescendants > maximum){
                maximum = nodes[nodes[now].children[i]].nOfDescendants;
                index = i;
            }
        }

        for(int i=0;i<nodes[now].children.size();i++){
            if(index == i){
                paths[nodes[now].children[i]] = paths[now];
            }
            else{
                paths[nodes[now].children[i]] = nodes[now].children[i];
            }
        }
    }


    //queries
    cin>>nOfqueries;
    for(int i=0;i<nOfqueries;i++){
        cin>>u>>v;
        while(paths[u] != paths[v]){
            int depthOfHeadU = nodes[paths[u]].depth;
            int depthOfHeadV = nodes[paths[v]].depth;
            if(depthOfHeadU > depthOfHeadV){
                u = nodes[paths[u]].parent;
            }
            else{
                v = nodes[paths[v]].parent;
            }
        }
        if(nodes[u].depth < nodes[v].depth){
            cout << u << endl;
        }
        else{
            cout << v << endl;
        }
    }

    return 0;
}
