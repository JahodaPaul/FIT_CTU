#include <bits/stdc++.h>
#define ll long long int

using namespace std;

int t;
vector<pair<ll,ll>> vector1;
ll x,y;
string st;

ll cross(ll x1, ll y1, ll x2, ll y2){
    return x1*y2 - x2*y1;
}

int main() {
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--){
        vector1.clear();
        cin>>x>>y;
        ll firstX = x,firstY = y;
        cin>>st;
        char prev = ' ';
        char first;
        first = st[0];
        for(int i=0;i<st.length();i++){
            if(prev != ' ' && prev != st[i] && st[i] != '.'){
                vector1.push_back(make_pair(x,y));
            }
            if(st[i] == 'E'){
                x+=1;
            }
            else if(st[i] == 'W'){
                x-=1;
            }
            else if(st[i] == 'N'){
                y+=1;
            }
            else if(st[i] == 'S'){
                y-=1;
            }
            else if(st[i] == '.'){
                if(first != prev){
                    vector1.push_back(make_pair(firstX,firstY));
                }
                continue;
            }
            prev = st[i];
        }
        ll sum = 0;
        for(int i=0;i<vector1.size();i++){
           sum += cross(vector1[i].first,vector1[i].second,vector1[(i+1)%vector1.size()].first,vector1[(i+1)%vector1.size()].second);
        }
        sum = abs(sum/2);
        cout << "The area is " <<sum << " squares." << endl;
    }
    return 0;
}