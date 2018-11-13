#include <bits/stdc++.h>

using namespace std;

string st;
int n,t;

struct Node{
    Node()
    {
        for(int i=0;i<26;i++){
            a[i]=NULL;
        }
        counter=0;
    }
    unsigned int counter;
    Node * a[26];
};

int main()
{
    Node * root = new Node;
    cin >> n;
    cin >> t;

    while(n--)
    {
        Node * word=root;
        cin >> st;
        int s=st.length();
        for(int i=0;i<s;i++){
            if(word->a[st[i]-'a']==NULL){
                word->a[st[i]-'a'] = new Node;
            }
            word->a[st[i]-'a']->counter+=1;
            word = word->a[st[i]-'a'];
        }
    }
    while(t--)
    {
        Node * word=root;
        cin >> st;
        bool b=true;
        for(int i=0;i<st.length();i++)
        {
            if(word->a[st[i]-'a']==NULL){
                cout << 0 << endl;
                b=false;
                break;
            }
            word = word->a[st[i]-'a'];
        }
        if(b){
            cout << word->counter << endl;}
    }
    return 0;
}
