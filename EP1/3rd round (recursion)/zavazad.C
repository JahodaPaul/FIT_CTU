#include <bits/stdc++.h>
#define ll long long int

using namespace std;

ll arr[31];

ll t,n,disk,current;

int main() {
    arr[0] = 0;
    arr[1] = 1;
    for(int i=2;i<=30;i++){
        arr[i] = arr[i-1] + arr[i-1] + 1;
    }
    cin>>t;
    while(t--){
        ll res = 0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>disk;
            if(i==1){
                current = disk;
            }
            else if(disk!=current) {
                res += arr[n - i] + 1;
                for (int j = 0; j < 3; j++) {
                    if (disk != j && current != j) {
                        current = j;
                        break;
                    }
                }
            }
        }
        cout << "Je treba "<< res << " presunu." << endl;
    }

    return 0;
}