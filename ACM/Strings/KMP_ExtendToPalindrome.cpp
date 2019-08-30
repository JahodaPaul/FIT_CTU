#include <bits/stdc++.h>

using namespace std;


string st;
char arr[200005];
int lps[200005];

void countPatternLPS(int lenOfPattern){
    int i,lenPrefixSuffix = 0;
    lps[0] = 0;
    i = 1;
    while(i<lenOfPattern){
        if(arr[i] == arr[lenPrefixSuffix]){
            lps[i] = lenPrefixSuffix + 1;
            i++;
            lenPrefixSuffix++;
        }
        else{
            if(lenPrefixSuffix != 0){
                lenPrefixSuffix = lps[lenPrefixSuffix - 1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of txt[] in pat[]
// N - len of string txt, M - len of pattern
int KMPSearch(char* pat, char* txt, int * lps,int M, int N)// M size of pattern, N size of string
{
    int res = 0;

    int i = 0, currLenPat=0;
    while(i < N){
        if(txt[i] == pat[currLenPat]){
            i++;
            currLenPat++;
            if(currLenPat == M){
                res++;
//                cout << "Found at pos " << i-M << endl;
                currLenPat = lps[currLenPat-1];
            }
        }
        else{
            if(currLenPat == 0){
                i++;
            }
            else{
                currLenPat = lps[currLenPat-1];
            }
        }
    }
    return res;
}

int main() {
    while(cin>>st){
        memset(lps,0,sizeof(lps));
        arr[st.length()] = '#';
        for(int i=st.length()-1;i>=0;i--){
            arr[st.length()-1-i] = st[i];
        }
        for(int i=0;i<st.length();i++){
            arr[st.length()+1+i] = st[i];
        }
        countPatternLPS(st.length()*2+1);
        for(int i=0;i<st.length();i++){
            cout << st[i];
        }
        for(int i=0;i<st.length()-lps[st.length()*2];i++){
            cout << arr[lps[st.length()*2] + i];
        }
        cout << endl;
    }
    return 0;
}