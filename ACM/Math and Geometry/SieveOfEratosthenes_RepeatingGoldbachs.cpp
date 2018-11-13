#include <bits/stdc++.h>

using namespace std;

int n;

int primes[1000007];

void SieveOfEratosthenes(int n)
{
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    vector<bool> prime;
    prime.resize((unsigned long)(n+1),true);

    for (int p=2; p*p<=n; ++p)
    {
        if (prime[p])
        {
            for (int i=p*2; i<=n; i += p)
                prime[i] = false;
        }
    }

    for (int p=2; p<=n; p++)
        if (prime[p])
            primes[p] = 1;
}

int main() {
    SieveOfEratosthenes(1000005);
    cin>>n;

    int smallIndex = 2;
    int result = 0;
    while(n >= 4){
        if(primes[n - smallIndex] == 1){
            n = (n - smallIndex) - smallIndex;
            smallIndex = 2;
            result++;
        }
        else{
            smallIndex++;
            while(!primes[smallIndex]){
                smallIndex++;
            }
        }
    }
    cout << result << endl;
    return 0;
}