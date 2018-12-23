#include <bits/stdc++.h>
#define ll long long int

using namespace std;

ll t;
vector<ll> arr;
vector<ll> dpArr;

int main() {
    scanf("%lld",&t);
    ll x = 0;
    ll cnt;
    ll m_size = 100000;
    arr.resize(m_size,0);
    while(t--){
        cnt = 0;
        while(1){
            scanf("%lld",&x);
            if(x==0){
                break;
            }
            if(cnt < m_size){
                arr[cnt] = x;
            }
            else{
                arr.emplace_back(x);
                m_size++;
            }
            cnt++;
        }
        dpArr.resize(cnt,0);
        if(cnt==0){
            printf("%lld\n",(ll)0);
            continue;
        }
        ll length = 0;
        for(int i=0;i<cnt;i++){
            auto it = upper_bound(dpArr.begin(),dpArr.begin()+length,arr[i]);
            if(it==dpArr.begin()+length){
                length++;
            }
            *it = arr[i];
        }
        printf("%lld\n",length);
    }

    return 0;
}