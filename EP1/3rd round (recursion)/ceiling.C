#include <bits/stdc++.h>

using namespace std;
int n,k;

struct Node{
    Node(){
        left = NULL;
        right = NULL;
    }
    int value;
    Node * left;
    Node * right;
};

vector<vector<int>> structures;

void AddValueToTree(int val, Node *& node){
    if(node == NULL){
        node = new Node;
        node->value = val;
        return;
    }
    Node * tmp = node;
    while(true){
        if(tmp->value < val){
            if(tmp->right == NULL){
                tmp->right = new Node;
                tmp->right->value = val;
                break;
            }
            tmp = tmp->right;
        }
        else{
            if(tmp->left == NULL){
                tmp->left = new Node;
                tmp->left->value = val;
                break;
            }
            tmp = tmp->left;
        }
    }
}

void AnalyzeTreeStructure(int horizontalDirFromRoot, int depth, Node * node, int index){
    if(node == NULL){
        return;
    }
    structures[index].push_back(horizontalDirFromRoot);
    structures[index].push_back(depth);
    AnalyzeTreeStructure(horizontalDirFromRoot-1,depth+1,node->left,index);
    AnalyzeTreeStructure(horizontalDirFromRoot+1,depth+1,node->right,index);
}

bool DoTheseTreeHaveSameStructure(vector<int> & a, vector<int> & b){
    for(int i=0;i<a.size();i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}

int arr[101];

int main() {
    while(cin>>n>>k){
        memset(arr,0,sizeof(arr));
        structures.clear();
        structures.resize(n,vector<int>());
        for(int i=0;i<n;i++){
            Node * root = NULL;
            int val;
            for(int j=0;j<k;j++){
                cin>>val;
                AddValueToTree(val,root);
            }
            AnalyzeTreeStructure(0,0,root,i);
        }

        int res = 1;
        for(int i=0;i<structures.size();i++){
            for(int j=i+1;j<structures.size();j++){
                if(arr[i] == 0 && arr[j] == 0){
                    if(DoTheseTreeHaveSameStructure(structures[i],structures[j])){
                        arr[j] = 1;
                    }
                }
            }
            if(arr[i] == 0){
                arr[i] = 1;
                res++;
            }
        }
        cout << res-1 << endl;
    }
    return 0;
}