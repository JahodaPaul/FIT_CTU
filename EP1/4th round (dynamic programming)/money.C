#include <bits/stdc++.h>

using namespace std;

double tmp;
string st,tmpString;
vector<int> arrCust;
vector<int> arrShop;

vector<int> dpTableCust;
vector<int> dpTableShop;
int target;

void getInput(bool negative){
    while(true){
        cin>>tmp;
        if(tmp == -1){
            break;
        }
        int number = (int)round(tmp*100);
        cin>>tmpString;
        st = "";
        for(int i=0;i<tmpString.size()-1;i++){
            st += tmpString[i];
        }
        int numberOfUnits = stoi(st);
        for(int i=0;i<numberOfUnits;i++){
            if(!negative) {
                arrCust.push_back(number);
            }
            else{
                arrShop.push_back(number);
            }
        }
    }
}

void dp(const vector<int> & arr, vector<int> & table){
    int mySum = 0;
    for(int i=0;i<arr.size();i++){
        mySum += arr[i];
    }
    table.resize(mySum+1);
    for(int i=0;i<mySum+1;i++){
        table[i] = -1;
    }
    for(int i=0;i<arr.size();i++){
        for(int j=mySum;j>=0;j--){
            if(table[j] != -1){
                if(table[j+arr[i]] == -1 || table[j+arr[i]] > table[j] + 1){
                    table[j+arr[i]] = table[j] + 1;
                }
            }
        }
        table[arr[i]] = 1;
    }
}


int main() {

    while(cin>>tmp){
        if(tmp == -1){
            return 0;
        }
        arrCust.clear();arrShop.clear();dpTableCust.clear();dpTableShop.clear();
        target = (int)round(tmp*100);
        getInput(false);
        getInput(true);

        dp(arrCust,dpTableCust);
        dp(arrShop,dpTableShop);

        int result = (target >= dpTableCust.size()? -1 : dpTableCust[target]);
        for(int i=target+1;i<dpTableCust.size();i++){
            if(i-target < dpTableShop.size() && dpTableCust[i] != -1 && dpTableShop[i-target] != -1){
                if(result == -1 || dpTableCust[i]+dpTableShop[i-target] < result){
                    result = dpTableCust[i]+dpTableShop[i-target];
                }
            }
        }

        if(result != -1){
            cout << result << " tenders must be exchanged." << endl;
        }
        else{
            cout << "The payment is impossible." << endl;
        }
    }
}
