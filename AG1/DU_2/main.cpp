#include <iostream>

using namespace std;

int what,n,low,high;
struct Node{
    Node(){
        value=0;
        nOfNodesBelow=0;
        left=NULL;
        right=NULL;
        parent = NULL;
        avlbalancing = 0;
        height = 0;
    }
    int avlbalancing;
    int value;
    int nOfNodesBelow;
    int height;
    Node * left;
    Node * right;
    Node * parent;
};

int balanceHeight(Node * left, Node * right){
    return right->height - left->height;
}

Node * RightRotate(Node *& node){
    Node *x = node->left;
    Node *T2 = x->right;

    x->right = node;
    node->left = T2;
    return x;
}

Node * LeftRotate(Node *& node){
    Node *y = node->right;
    Node *T2 = y->left;

    y->left = node;
    node->right = T2;
    return y;
}

int Balance(Node *& node){
    if(node->right != NULL && node->left != NULL){
        node->right->parent = node;
        node->left->parent = node;
        node->height = max(node->right->height,node->left->height)+1;
        node->avlbalancing = balanceHeight(node->left,node->right);
        return (2+node->right->nOfNodesBelow+node->left->nOfNodesBelow);
    }
    else if(node->left == NULL && node->right != NULL){
        node->avlbalancing = 1;
        node->right->parent = node;
        node->height = node->right->height+1;
        return (1+node->right->nOfNodesBelow);
    }
    else if(node->right == NULL && node->left != NULL){
        node->avlbalancing = -1;
        node->left->parent = node;
        node->height = node->left->height+1;
        return (1+node->left->nOfNodesBelow);
    }
    else{
        node->avlbalancing = 0;
        node->height = 0;
        return 0;
    }
}

void BalanceRoot(Node *& tmpRoot){
    int l = Balance(tmpRoot->left);
    int r = Balance(tmpRoot->right);
    tmpRoot->height = max(tmpRoot->left->height,tmpRoot->right->height)+1;
    tmpRoot->avlbalancing=balanceHeight(tmpRoot->left,tmpRoot->right);
    tmpRoot->left->nOfNodesBelow = l;
    tmpRoot->right->nOfNodesBelow = r;
    tmpRoot->nOfNodesBelow = (2+l+r);
    tmpRoot->left->parent = tmpRoot;
    tmpRoot->right->parent = tmpRoot;
}

Node * root;

void ConnectSuperParentToNewRoot(Node *& tmp){
    if(tmp->parent != NULL){
        if(tmp->value > tmp->parent->value){
            tmp->parent->right = tmp;
        }
        else{
            tmp->parent->left = tmp;
        }
    }
}

void PropageUpwards(Node *& tmp){
    while(tmp->parent != NULL){
        if(tmp->parent->left == tmp){
            tmp->parent->avlbalancing--;
            if(tmp->parent->avlbalancing < 0) {
                tmp->parent->height++;
            }
        }
        else if(tmp->parent->right == tmp){
            tmp->parent->avlbalancing++;
            if(tmp->parent->avlbalancing > 0) {
                tmp->parent->height++;
            }
        }
        if(tmp->parent->avlbalancing==0){
            return;
        }

        if(tmp->parent->avlbalancing<-1){
            if(tmp->parent->left != NULL && tmp->parent->left->avlbalancing == -1){//left left
                tmp = RightRotate(tmp->parent);
                tmp->parent = tmp->right->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            else if(tmp->parent->left != NULL && tmp->parent->left->avlbalancing == 1){//left right
                tmp->parent->left = LeftRotate(tmp->parent->left);
                tmp = RightRotate(tmp->parent);
                tmp->parent = tmp->right->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            return;
        }
        else if(tmp->parent->avlbalancing>1){
            if(tmp->parent->right != NULL && tmp->parent->right->avlbalancing == 1){//right right
                tmp = LeftRotate(tmp->parent);
                tmp->parent = tmp->left->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            else if(tmp->parent->right != NULL && tmp->parent->right->avlbalancing == -1){//right left
                tmp->parent->right = RightRotate(tmp->parent->right);
                tmp = LeftRotate(tmp->parent);
                tmp->parent = tmp->left->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            return;
        }
        tmp = tmp->parent;
    }
}

void PropageUpwardsDelete(Node *& tmp){
    while(tmp != NULL){
        if(tmp->right != NULL && tmp->left != NULL){
            tmp->height = max(tmp->left->height,tmp->right->height)+1;
            tmp->avlbalancing = tmp->right->height - tmp->left->height;
        }
        else if(tmp->right != NULL){
            tmp->height = tmp->right->height+1;
            tmp->avlbalancing = tmp->right->height - 0;
        }
        else if(tmp->left != NULL){
            tmp->height = tmp->left->height+1;
            tmp->avlbalancing = 0 - tmp->left->height;
        }
        else{
            tmp->height = 0;
            tmp->avlbalancing = 0;
        }

        if(tmp->avlbalancing<-1){
            if(tmp->left != NULL && tmp->left->avlbalancing == -1){//left left
                tmp = RightRotate(tmp);
                tmp->parent = tmp->right->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            else if(tmp->left != NULL && tmp->left->avlbalancing == 1){//left right
                tmp->left = LeftRotate(tmp->left);
                tmp = RightRotate(tmp);
                tmp->parent = tmp->right->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            return;
        }
        else if(tmp->avlbalancing>1){
            if(tmp->right != NULL && tmp->right->avlbalancing == 1){//right right
                tmp = LeftRotate(tmp);
                tmp->parent = tmp->left->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            else if(tmp->right != NULL && tmp->right->avlbalancing == -1){//right left
                tmp->right = RightRotate(tmp->right);
                tmp = LeftRotate(tmp);
                tmp->parent = tmp->left->parent;
                ConnectSuperParentToNewRoot(tmp);
                BalanceRoot(tmp);
            }
            return;
        }
        tmp = tmp->parent;
    }
}

int main() {
    ios::sync_with_stdio(0);
    root = NULL;
    while(cin>>what){
        if(what==1){
            //add
            cin>>n;
            if(root==NULL){
                root=new Node();
                root->value=n;
            }
            else{
                Node * tmp = root;
                while(true){
                    if(n>tmp->value){
                        if(tmp->right==NULL){
                            tmp->nOfNodesBelow+=1;
                            tmp->right = new Node();
                            tmp->right->parent = tmp;
                            tmp->right->value = n;
                            //propage upwards
                            tmp = tmp->right;
                            PropageUpwards(tmp);
                            while(root->parent != NULL){
                                root = root->parent;
                            }
                            break;
                        }
                        else{
                            tmp->nOfNodesBelow+=1;
                            tmp=tmp->right;
                        }
                    }
                    else{
                        if(tmp->left==NULL){
                            tmp->nOfNodesBelow+=1;
                            tmp->left = new Node();
                            tmp->left->parent = tmp;
                            tmp->left->value = n;
                            //propage upwards
                            tmp = tmp->left;
                            PropageUpwards(tmp);
                            while(root->parent != NULL){
                                root = root->parent;
                            }
                            break;
                        }
                        else{
                            tmp->nOfNodesBelow+=1;
                            tmp=tmp->left;
                        }
                    }
                }
            }

        }
        else if(what==3){
            //look for
            cin>>low>>high;
            bool notFound = false;
            Node * newRoot = root;
            int positionLeft,positionRight,positonTmp=0;
            while((newRoot != NULL) && (newRoot->value > high || newRoot->value < low)){
                if(newRoot->value > high){
                    newRoot=newRoot->left;
                }
                else if(newRoot->value < low){
                    if(newRoot->left != NULL){
                        positonTmp += (1+newRoot->left->nOfNodesBelow);
                    }
                    positonTmp++;
                    newRoot=newRoot->right;
                }
            }
            if(newRoot==NULL){
                cout << "notfound" << endl;
                notFound=true;
            }
            if(!notFound){
                if(newRoot->left != NULL){
                    positonTmp += (1+newRoot->left->nOfNodesBelow);
                }
                Node * lowNode;
                Node * highNode;
                if(newRoot->left == NULL && newRoot->right==NULL){
                    cout << newRoot->value << endl;
                    continue;
                }
                highNode = newRoot;
                lowNode = newRoot;
                positionLeft = positonTmp;
                positionRight = positonTmp;
                int posLeftPrevious = positionLeft;
                int posRightPrevious = positionRight;


                //left side
                while(lowNode != NULL){
                    if(lowNode->value==low){
                        break;
                    }
                    else if(lowNode->value > low){
                        if(lowNode->left == NULL){
                            break;
                        }
                        if(lowNode->left->value < low && lowNode->value >= low){
                            posLeftPrevious = positionLeft;
                        }
                        lowNode = lowNode->left;
                        if (lowNode->right != NULL) {
                            positionLeft -= (1 + lowNode->right->nOfNodesBelow);
                        }
                        positionLeft--;
                    }
                    else if(lowNode->value < low){
                        if(lowNode->right==NULL){
                            break;
                        }
                        lowNode = lowNode->right;
                        if(lowNode->left != NULL){
                            positionLeft += (1+lowNode->left->nOfNodesBelow);
                        }
                        positionLeft++;
                    }
                }
                if(lowNode->value < low){
                    positionLeft = posLeftPrevious;
                }

                //right side
                while(highNode != NULL){
                    if(highNode->value==high){
                        break;
                    }
                    else if(highNode->value < high){
                        if(highNode->right == NULL){
                            break;
                        }
                        if(highNode->right->value > high && highNode->value <= high){
                            posRightPrevious = positionRight;
                        }
                        highNode = highNode->right;
                        if (highNode->left != NULL) {
                            positionRight += (1 + highNode->left->nOfNodesBelow);
                        }
                        positionRight++;
                    }
                    else if(highNode->value > high){
                        if(highNode->left == NULL){
                            break;
                        }
                        highNode = highNode->left;
                        if(highNode->right != NULL){
                            positionRight -= (1+highNode->right->nOfNodesBelow);
                        }
                        positionRight--;
                    }
                }
                if(highNode->value > high){
                    positionRight = posRightPrevious;
                }

                //finding median
                Node * median = newRoot;
                int currentPosition = positonTmp;
                int medianPosition = (positionLeft+positionRight)/2;
                while(true){
                    if(currentPosition == medianPosition){
                        cout << median->value << endl;
                        break;
                    }
                    if(currentPosition > medianPosition){
                        median = median->left;
                        if(median->right != NULL){
                            currentPosition -= (1+median->right->nOfNodesBelow);
                        }
                        currentPosition--;
                    }
                    else{
                        median = median->right;
                        if(median->left != NULL){
                            currentPosition += (1+median->left->nOfNodesBelow);
                        }
                        currentPosition++;
                    }
                }
            }
            
        }
        else if(what==2){
            //delete
            cin>>n;

            Node * toBeDeleted = root;
            while(toBeDeleted!=NULL){
                if(toBeDeleted->value==n){
                    //lower the numberofNodes below for each parent
                    Node * lower = toBeDeleted;
                    while(lower->parent != NULL){
                        lower->parent->nOfNodesBelow--;
                        lower= lower->parent;
                    }
                    if(toBeDeleted->right==NULL && toBeDeleted->left==NULL){//if leaf
                        if(toBeDeleted->parent!=NULL){
                            if(toBeDeleted->parent->left==toBeDeleted){
                                toBeDeleted=toBeDeleted->parent;
                                delete (toBeDeleted->left);
                                toBeDeleted->left = NULL;
                                PropageUpwardsDelete(toBeDeleted);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                            else{
                                toBeDeleted=toBeDeleted->parent;
                                delete (toBeDeleted->right);
                                toBeDeleted->right = NULL;
                                PropageUpwardsDelete(toBeDeleted);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                        }
                        else{
                            delete toBeDeleted;
                            root=NULL;
                        }
                    }
                    else if(toBeDeleted->right==NULL || toBeDeleted->left==NULL){//if one child
                        if(toBeDeleted->right==NULL){
                            if(toBeDeleted->parent==NULL){//if root
                                root = toBeDeleted->left;
                                toBeDeleted = toBeDeleted->left;
                                delete (toBeDeleted->parent);
                                toBeDeleted->parent = NULL;
                                PropageUpwardsDelete(toBeDeleted);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                            else{
                                Node * parent = toBeDeleted->parent;
                                toBeDeleted->left->parent = toBeDeleted->parent;
                                if(toBeDeleted->parent->left == toBeDeleted){
                                    toBeDeleted->parent->left = toBeDeleted->left;
                                }
                                else if(toBeDeleted->parent->right == toBeDeleted){
                                    toBeDeleted->parent->right = toBeDeleted->left;
                                }
                                delete toBeDeleted;
                                PropageUpwardsDelete(parent);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                        }
                        else{//if right child is not NULL
                            if(toBeDeleted->parent==NULL){//if root
                                root = toBeDeleted->right;
                                toBeDeleted = toBeDeleted->right;
                                delete (toBeDeleted->parent);
                                toBeDeleted->parent = NULL;
                                PropageUpwardsDelete(toBeDeleted);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                            else{
                                Node * parent = toBeDeleted->parent;
                                toBeDeleted->right->parent = toBeDeleted->parent;
                                if(toBeDeleted->parent->left == toBeDeleted){
                                    toBeDeleted->parent->left = toBeDeleted->right;
                                }
                                else if(toBeDeleted->parent->right == toBeDeleted){
                                    toBeDeleted->parent->right = toBeDeleted->right;
                                }
                                delete toBeDeleted;
                                PropageUpwardsDelete(parent);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                        }
                    }
                    else{//if two children
                        toBeDeleted->nOfNodesBelow--;
                        if(toBeDeleted->right->nOfNodesBelow >= toBeDeleted->left->nOfNodesBelow){//find leftMost to the right
                            Node * leftMost = toBeDeleted->right;
                            while(leftMost->left != NULL){
                                leftMost->nOfNodesBelow--;
                                leftMost = leftMost->left;
                            }
                            toBeDeleted->value = leftMost->value;
                            if(leftMost->right != NULL){
                                Node * parent = leftMost->parent;
                                if(leftMost->parent->left == leftMost) {
                                    leftMost->parent->left = leftMost->right;
                                }
                                else{
                                    leftMost->parent->right = leftMost->right;
                                }

                                if(leftMost->right != NULL) {
                                    leftMost->right->parent = leftMost->parent;
                                }
                                delete leftMost;
                                PropageUpwardsDelete(parent);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                            else{
                                Node * parent = leftMost->parent;
                                if(leftMost->parent->left == leftMost) {
                                    leftMost->parent->left = NULL;
                                }
                                else{
                                    leftMost->parent->right = NULL;
                                }
                                delete leftMost;
                                PropageUpwardsDelete(parent);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }

                        }
                        else{//find rightmost to left
                            Node * rightMost = toBeDeleted->left;
                            while(rightMost->right != NULL){
                                rightMost->nOfNodesBelow--;
                                rightMost = rightMost->right;
                            }
                            toBeDeleted->value = rightMost->value;
                            if(rightMost->left != NULL){
                                Node * parent = rightMost->parent;
                                if(rightMost->parent->right == rightMost) {
                                    rightMost->parent->right = rightMost->left;
                                }
                                else{
                                    rightMost->parent->left = rightMost->left;
                                }

                                if(rightMost->left != NULL) {
                                    rightMost->left->parent = rightMost->parent;
                                }
                                delete rightMost;
                                PropageUpwardsDelete(parent);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                            else{
                                Node * parent = rightMost->parent;
                                if(rightMost->parent->right == rightMost) {
                                    rightMost->parent->right = NULL;
                                }
                                else{
                                    rightMost->parent->left = NULL;
                                }
                                delete rightMost;
                                PropageUpwardsDelete(parent);
                                while(root->parent != NULL){
                                    root = root->parent;
                                }
                                break;
                            }
                        }

                    }
                    break;
                }
                else if(toBeDeleted->value > n){
                    toBeDeleted = toBeDeleted->left;
                }
                else if(toBeDeleted->value < n){
                    toBeDeleted = toBeDeleted->right;
                }
            }
        }
        else if(what==4){ return 0;}
    }

    return 0;
}