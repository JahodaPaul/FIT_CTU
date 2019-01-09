#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int t,lengthOfEachStep,numberOfSections;

double arr[5001];

int main() {
    cin>>t;
    while(t--){
        cin>>lengthOfEachStep>>numberOfSections;
        for(int i=0;i<numberOfSections;i++){
            cin>>arr[i];
        }
        int index = 0;
        double restOfSection = arr[0];
        double remaining = 0;
        ll res = 0;
        while(index < numberOfSections){
            ll tmp = 0;
            tmp = floor(restOfSection/lengthOfEachStep);
            restOfSection-=tmp*lengthOfEachStep;
            res += tmp;
            remaining = restOfSection;
            if(index+1 < numberOfSections){
                if(remaining <= 0.000001){
                    remaining = 0;
                }
                restOfSection = arr[index+1] - sqrt(lengthOfEachStep*lengthOfEachStep-remaining*remaining);
                res++;
            }
            index++;
        }
        if(remaining >= lengthOfEachStep/2.0){
            res+=1;
        }
        cout << "Strazny ujde "<< res <<" ponorku." << endl;
    }
    return 0;
}