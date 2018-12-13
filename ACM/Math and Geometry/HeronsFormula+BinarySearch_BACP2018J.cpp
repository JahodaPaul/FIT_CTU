#include <bits/stdc++.h>
#define ll long long int

using namespace std;

ll a,b,c,d;

double HeronsFormula(double side1, double side2, double side3){
    double s = (side1+side2+side3)/(double)2;
    return sqrt(s*(s-side1)*(s-side2)*(s-side3));
}

double AreaOfPolygonFourVertices(double lineFromTwoOppositePoints){
    if(a+b<lineFromTwoOppositePoints || c+d<lineFromTwoOppositePoints){
        return -1;
    }
    return HeronsFormula(a,b,lineFromTwoOppositePoints) + HeronsFormula(c,d,lineFromTwoOppositePoints);
}

double BinSearch(){
    ll left = 0, right = 2000*(1e6);
    while(left<right){
        ll m = (left+right)/2;
        if(AreaOfPolygonFourVertices(m-1) >= AreaOfPolygonFourVertices(m+1)){
            right = m - 1;
        }
        else{
            left = m + 1;
        }
    }
    return left/(1e6);
}

int main() {
    cin>>a>>b>>c>>d;
    a*=(1e6);b*=(1e6);c*=(1e6);d*=(1e6);
    double line = BinSearch();
    a/=(1e6);b/=(1e6);c/=(1e6);d/=(1e6);
    cout << setprecision(6) << fixed << AreaOfPolygonFourVertices(line) << endl;
    return 0;
}