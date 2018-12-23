#include <bits/stdc++.h>

using namespace std;

int t;
string st;

int main() {
    ios::sync_with_stdio(0);
    cin>>t;
    cin.ignore();
    for(int i=0;i<t;i++){
        getline (std::cin,st);
        vector<int> ress;
        bool correct = true;
        for(int j=0;j<st.length();j++){
            if(j+1 < st.length() && ((st[j] == '(' && st[j+1] == '*') || (st[j] == '*' && st[j+1] == ')'))){
                if(st[j] == '(' && st[j+1] == '*'){
                    ress.push_back(0);
                }
                else{
                    if(ress.size() == 0 || ress.back() != 0){
                        correct = false;
                        break;
                    }
                    else{
                        ress.pop_back();
                    }
                }
                j++;
            }
            else if(st[j] == '(' || st[j] == ')' || st[j] == '[' || st[j] == ']' || st[j] == '{' || st[j] == '}' || st[j] == '<' || st[j] == '>'){
                if(st[j] == '('){
                    ress.push_back(1);
                }
                else if(st[j] == ')'){
                    if(ress.size() == 0 || ress.back() != 1){
                        correct = false;
                        break;
                    }
                    else{
                        ress.pop_back();
                    }
                }
                else if(st[j] == '['){
                    ress.push_back(2);
                }
                else if(st[j] == ']'){
                    if(ress.size() == 0 || ress.back() != 2){
                        correct = false;
                        break;
                    }
                    else{
                        ress.pop_back();
                    }
                }
                else if( st[j] == '{'){
                    ress.push_back(3);
                }
                else if( st[j] == '}'){
                    if(ress.size() == 0 || ress.back() != 3){
                        correct = false;
                        break;
                    }
                    else{
                        ress.pop_back();
                    }
                }
                else if(st[j] == '<'){
                    ress.push_back(4);
                }
                else if(st[j] == '>'){
                    if(ress.size() == 0 || ress.back() != 4){
                        correct = false;
                        break;
                    }
                    else{
                        ress.pop_back();
                    }
                }
            }
        }
        if(correct && ress.size() == 0){
            cout << "Plan je v poradku." << endl;
        }
        else{
            cout << "V planu je chyba." << endl;
        }
    }
    return 0;
}