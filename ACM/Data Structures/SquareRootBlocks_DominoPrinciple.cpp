#include <bits/stdc++.h>

using namespace std;

struct SingleDominoPiece{
    int index;
    int height;
    int position;
};
vector<SingleDominoPiece> v1;
int indexes[100005];
int block[1000];
int toWhatIndexDoesItFall[100005];

int blockSize;
int n;

int main() {
    ios::sync_with_stdio(0);
    cin>>n;
    int blockSize = (int)sqrt(n);
    v1.resize((unsigned long)n,SingleDominoPiece());
    int pos,length;
    for(int i=0;i<n;i++){
        cin>>pos>>length;
        v1[i].index=i;
        v1[i].height = length;
        v1[i].position = pos;
    }
    sort(v1.begin(),v1.end(),[](const SingleDominoPiece & a, const SingleDominoPiece & b){return a.position < b.position;});
    for(int i=0;i<v1.size();i++){
        indexes[v1[i].index] = i;
    }

    SingleDominoPiece tmp;
    for(int i=n-1;i>=0;i--){
        tmp.position = v1[i].position+v1[i].height;
        auto it = lower_bound(v1.begin(),v1.end(),tmp,[](const SingleDominoPiece & a, const SingleDominoPiece & b){return a.position < b.position;});
        int index = it-v1.begin();
        int maxFound = -1;
        index--;
        for(int j=i+1;j<=index;j++){
            while(j%(blockSize) == 0 && j+blockSize < index){
                if(block[j/blockSize] > maxFound){
                    maxFound = block[j/blockSize];
                }
                j+=blockSize;
            }
            if(toWhatIndexDoesItFall[j] > maxFound){
                maxFound = toWhatIndexDoesItFall[j];
            }
        }
        if(maxFound == -1){maxFound=index;}
        if(block[i/blockSize] < maxFound){
            block[i/blockSize] = maxFound;
        }
        toWhatIndexDoesItFall[i] = maxFound;
    }
    for(int i=0;i<n;i++){
        cout << toWhatIndexDoesItFall[indexes[i]]-indexes[i]+1 << " ";
    }
    cout << endl;
    return 0;
}