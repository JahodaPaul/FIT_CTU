#include <bits/stdc++.h>

using namespace std;
vector<string> v;

string line1 = "";
string line2 = "";

pair<int,int> getPosition(char c, char i){
    int col = c-'a';
    int row = 7-(i-'1');
    row = 2*row+1;
    col = 4*col+2;
    return make_pair(row,col);
}

void Function(bool white,string line){
    for(int i=7;i<line.size();i++){
        pair<int,int> pos;
        int cnt = i;
        string item = "";
        while(cnt < line.size() && line[cnt] != ','){
            item+=line[cnt];
            cnt++;
        }
        i=cnt;
        if(item.size() == 3){
            pos = getPosition(item[1],item[2]);
            if(!white){
                v[pos.first][pos.second] = (char)(item[0]-'A'+'a');
            }
            else{
                v[pos.first][pos.second] = item[0];
            }
        }
        else if(item.size() == 2){
            pos = getPosition(item[0],item[1]);
            if(!white){
                v[pos.first][pos.second] = 'p';
            }
            else{
                v[pos.first][pos.second] = 'P';
            }
        }
    }
}

int main() {

    getline(std::cin,line1);
    getline(std::cin,line2);

    for(int i=0;i<17;i++){
        string line = "";
        for(int j=0;j<8;j++){
            if(i%2==0){
                line+="+---";
            }
            else{
                if( (j%2==0 && (i-1)%4==0) || (j%2!=0 && (i-1)%4!=0)){
                    line += "|...";
                }
                else{
                    line += "|:::";
                }
            }
        }
        if(i%2==0){
            line+="+";
        }
        else{
            line+="|";
        }
        v.push_back(line);
    }

    Function(true,line1);
    Function(false,line2);

    for(int i=0;i<v.size();i++){
        cout << v[i] << endl;
    }
    return 0;
}