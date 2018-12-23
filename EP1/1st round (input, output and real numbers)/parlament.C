#include <bits/stdc++.h>

using namespace std;

int t,nOfRows,nOfCols,d;
int arr[1001][1001];
int square[1001][1001];

int main() {
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--){
        cin>>nOfRows>>nOfCols;
        for(int i=0;i<nOfRows;i++){
            for(int j=0;j<nOfCols;j++){
                cin>>arr[i][j];
                if(i==0){
                    if(j==0){
                        square[i][j] = arr[i][j];
                    }
                    else{
                        square[i][j] = arr[i][j] + square[i][j-1];
                    }
                }
                else if(j==0){
                    square[i][j] = arr[i][j] + square[i-1][j];
                }
                else{
                    square[i][j] = arr[i][j] + square[i-1][j] + square[i][j-1] - square[i-1][j-1];
                }
            }
        }
        cin>>d;
        while(d--){
            int r1,c1,r2,c2;
            cin>>r1>>c1>>r2>>c2;
            r1--;
            r2--;
            c1--;
            c2--;
            int result = square[r2][c2];
            if(r1 > 0){
                result -= square[r1-1][c2];
            }
            if(c1 > 0){
                result -= square[r2][c1-1];
            }
            if(r1 > 0 && c1 > 0){
                result += square[r1-1][c1-1];
            }
            cout << "Absolutni hodnota pohodlnosti je " << result << " bodu." << endl;
        }
        cout << endl;
    }
    return 0;
}