#include <bits/stdc++.h>

using namespace std;

priority_queue<int, vector<int>, greater<int>> smallestTop;
priority_queue<int, vector<int>, less<int>> greatestTop;

string tmp;

void RebalanceGreatestTop(){
    while(greatestTop.size() > smallestTop.size()){
        int temporary = greatestTop.top();
        greatestTop.pop();
        smallestTop.push(temporary);
    }
}

void RebalanceSmallestTop(){
    while(smallestTop.size() > greatestTop.size() + 1){
        int temporary = smallestTop.top();
        smallestTop.pop();
        greatestTop.push(temporary);
    }
}

int main() {
    ios::sync_with_stdio(0);
    while(cin>>tmp) {
        if (tmp == "#"){
            cout << smallestTop.top() << endl;
            smallestTop.pop();
            RebalanceGreatestTop();
        }
        else{
            int integer = stoi(tmp);
            if(smallestTop.empty() || (!greatestTop.empty() && integer > greatestTop.top())){
                smallestTop.push(integer);
                RebalanceSmallestTop();
            }
            else{
                greatestTop.push(integer);
                RebalanceGreatestTop();
            }
        }
    }

    return 0;
}