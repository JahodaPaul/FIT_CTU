#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node(){
        right = NULL;
        left = NULL;
        number = 0;
    }
    void SetCoordinates(int l,int r){
        leftCoordinate = l;
        rightCoordinate = r;
    }
    Node * right;
    Node * left;
    int leftCoordinate;
    int rightCoordinate;
    int number;
};

inline int read() {
    register int c=getchar();int x=0;
    for(;c<48||c>57;c=getchar());
    for(;c>47&&c<58;c=getchar())
        x=(x<<1)+(x<<3)+c-48;
    return x;
}

Node * root;

inline void Check(Node *& node,int l,int r){
    if(node==NULL){
        node = new Node();
        node->SetCoordinates(l,r);
    }
}

void IncreaseFromAToBByY(int l,int r, int y,Node *& node){
    if (node->leftCoordinate >= l && node->rightCoordinate <= r){
        node->number += y;
        return;
    }
    Check(node->left,node->leftCoordinate,(node->leftCoordinate+node->rightCoordinate)/2);
    Check(node->right,((node->leftCoordinate + node->rightCoordinate) / 2) + 1,node->rightCoordinate);
    if(node->right->leftCoordinate > r && node->left->rightCoordinate >= l){
        IncreaseFromAToBByY(l,r,y,node->left);
    }
    else if(node->left->rightCoordinate < l && node->right->leftCoordinate <= r){
        IncreaseFromAToBByY(l,r,y,node->right);
    }
    else{
        IncreaseFromAToBByY(l,r,y,node->left);
        IncreaseFromAToBByY(l,r,y,node->right);
    }
}

int n,a,b,y,l;
string st;

int main() {

    while(cin>>n){
        root = new Node();
        root->SetCoordinates(1,100000);
        for(int i=0;i<n;i++){
            cin >> st;
            if(st=="B"){
                a = read();
                b = read();
                y = read();
                Node * rootNow = root;
                IncreaseFromAToBByY(a,b,y,rootNow);
            }
            else{
                l = read();
                Node * tmp = root;
                int current = tmp->number;
                while(1){
                    if(tmp->right!=NULL && tmp->right->rightCoordinate >= l && tmp->right->leftCoordinate <= l){
                        tmp = tmp->right;
                        current += tmp->number;
                    }
                    else if(tmp->left!=NULL && tmp->left->rightCoordinate >= l && tmp->left->leftCoordinate <= l){
                        tmp = tmp->left;
                        current += tmp->number;
                    }
                    else{
                        break;
                    }
                }
                cout << current << endl;
            }
        }
        //DELETE TREE
        queue<Node *> q;
        q.push(root);
        while(!q.empty())
        {
            Node * tmp = q.front();
            q.pop();
            if(tmp->left != NULL){
                q.push(tmp->left);
            }
            if(tmp->right != NULL){
                q.push(tmp->right);
            }
            delete tmp;
        }
    }
    return 0;
}
