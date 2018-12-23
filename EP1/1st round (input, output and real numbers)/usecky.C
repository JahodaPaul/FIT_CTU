#include <bits/stdc++.h>

using namespace std;

int n;
vector<double> vector1;
double X1,Y1,X2,Y2,maxx;

double getlen(double x1,double y1,double x2,double y2 ){
    return sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) );
}

int main() {
    while(1){
        cin>>n;
        if(n==0){
            break;
        }
        maxx = -1.0;
        vector1.clear();
        for(int i=0;i<n;i++){
            cin>>X1>>Y1>>X2>>Y2;
            vector1.push_back(getlen(X1,Y1,X2,Y2));
        }

        for(auto & item: vector1){
            if(item > maxx){
                maxx = item;
            }
        }
        int res = 0;
        double epsilon = maxx/(double)1e14; //rather bigger than smaller
        for(auto & item: vector1){
            if(abs(maxx-item) < epsilon){
                res++;
            }
        }
        cout << res << " usecek ma delku " << fixed << setprecision(2) << maxx << "." << endl;
    }

    return 0;
}