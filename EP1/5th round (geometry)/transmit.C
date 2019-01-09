#include <bits/stdc++.h>
# define M_PI           3.14159265358979323846  /* pi */

using namespace std;

vector<double> degrees;
double transmitterX, transmitterY, radius;
int n;

double euclideanDistance(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

bool IsInOneOfTheTwoHemispheres(double degree1, double degree2){
    if(degree2>=degree1 && degree2-degree1 <= 180){
        return true;
    }
    if(degree2<degree1 && degree1-degree2 >= 180){
        return true;
    }
    return false;
}

int main() {
    while(cin>>transmitterX>>transmitterY>>radius){
        if(radius<0){
            return 0;
        }
        cin>>n;
        degrees.clear();
        int x,y;
        for(int i=0;i<n;i++){
            cin>>x>>y;
            if(euclideanDistance(x,y,transmitterX,transmitterY) <= radius){
                degrees.push_back(180+180*atan2(y-transmitterY,x-transmitterX)/M_PI);
            }
        }
        int maximum = 0;
        for(int i =0;i<degrees.size();i++){
            int sum = 1;
            for(int j=0;j<degrees.size();j++){
                if(i!=j){
                    if(IsInOneOfTheTwoHemispheres(degrees[i],degrees[j])){
                        sum++;
                    }
                }
            }
            if(degrees.size()-sum > sum){
                sum = degrees.size()-sum;
            }
            if(sum>maximum){
                maximum = sum;
            }
        }
        cout << maximum << endl;
    }
}