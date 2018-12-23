#include <bits/stdc++.h>

using namespace std;
int n;
int arrX[101];
int arrY[101];

int X1,X2,Y1,Y2;
int setX,setY;
int flagEnd = 0;

pair<int,int> findOverlap(int one,int two,int three,int four){
    vector<int> tmp;
    tmp.push_back(one);
    tmp.push_back(two);
    tmp.push_back(three);
    tmp.push_back(four);
    sort(tmp.begin(),tmp.end());
    int temporary = 0;
    if(one > two){
        temporary = two;
        two = one;
        one = temporary;
    }
    if( ((one == tmp[0] && two == tmp[1]) || (one == tmp[2] && two == tmp[3])) && tmp[1] != tmp[2] ){
        flagEnd = 1;
        return pair<int,int>();
    }
    return make_pair(tmp[1],tmp[2]);
}

int main() {
    int cnt = 0;
    while(cin>>n){
        if(n==0){return 0;}
        cnt++;
        X1=0;X2=0;Y1=0;Y2=0;
        setX = 0;
        setY = 0;
        flagEnd = 0;
        int x,y;
        for(int i=0;i<n;i++){
            cin>>arrX[i]>>arrY[i];
        }
        for(int i=0;i<n;i++){
            bool b = false;
            if(arrX[i] - arrX[(i+1)%n] > 0 && arrX[(i+2)%n] - arrX[(i+3)%n] < 0) {
                b = true;
            }
            else if(arrX[i] - arrX[(i+1)%n] < 0 && arrX[(i+2)%n] - arrX[(i+3)%n] > 0) {
                b = true;
            }
            else if(arrY[i] - arrY[(i+1)%n] > 0 && arrY[(i+2)%n] - arrY[(i+3)%n] < 0) {
                b=true;
            }
            else if(arrY[i] - arrY[(i+1)%n] < 0 && arrY[(i+2)%n] - arrY[(i+3)%n] > 0) {
                b=true;
            }

            if(b){
                int diffX = arrX[(i+1)%n] - arrX[(i+2)%n];
                int diffY = arrY[(i+1)%n] - arrY[(i+2)%n];
                if(diffX != 0){
                    if(!setX){
                        setX = 1;
                        X1 = arrX[(i+1)%n];
                        X2 = arrX[(i+2)%n];
                    }
                    else{
                        pair<int,int> tmp = findOverlap(X1,X2,arrX[(i+1)%n],arrX[(i+2)%n]);
                        X1 = tmp.first;
                        X2 = tmp.second;
                    }
                }
                else if(diffY != 0){
                    if(!setY){
                        setY = 1;
                        Y1 = arrY[(i+1)%n];
                        Y2 = arrY[(i+2)%n];
                    }
                    else{
                        pair<int,int> tmp = findOverlap(Y1,Y2,arrY[(i+1)%n],arrY[(i+2)%n]);
                        Y1 = tmp.first;
                        Y2 = tmp.second;
                    }
                }
                if(flagEnd){
                    cout << "Floor #"<< cnt << endl;
                    cout << "Surveillance is impossible." << endl;
                    cout << endl;
                    break;
                }
            }
        }
        if(!flagEnd){
            cout << "Floor #"<< cnt << endl;
            cout << "Surveillance is possible." << endl;
            cout << endl;
        }

    }
}