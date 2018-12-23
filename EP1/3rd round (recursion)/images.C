#include <bits/stdc++.h>

using namespace std;

string st1,st2;
string tmp1, tmp2;

char hexa[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

string CheckIfItsSingleDigitBinN(string & a){
    if(a == "0" || a == "1"){
        return "1" + a;
    }
    return a;
}

int in1;
int in2;

string recursion(int index1, int index2,bool firstPic, bool secondPic){
    if(!firstPic && tmp2[index2] == '1'){
        string s(1, tmp2[index2+1]);
        in2 = index2 + 2;
        return s;
    }
    if(!secondPic && tmp1[index1] == '1'){
        string s(1, tmp1[index1+1]);
        in1 = index1 + 2;
        return s;
    }
    if(!firstPic){
        string a1 = recursion(index1,index2+1,firstPic,secondPic);
        string a2 = recursion(index1,in2,firstPic,secondPic);
        string a3 = recursion(index1,in2,firstPic,secondPic);
        string a4 = recursion(index1,in2,firstPic,secondPic);
        if(a1 == a2 && a2 == a3 && a3 == a4 && (a4 == "1" || a4 == "0")){
            return a1;
        }
        else{
            a1 = CheckIfItsSingleDigitBinN(a1);
            a2 = CheckIfItsSingleDigitBinN(a2);
            a3 = CheckIfItsSingleDigitBinN(a3);
            a4 = CheckIfItsSingleDigitBinN(a4);
            return "0" + a1 + a2 + a3 + a4;
        }
    }
    if(!secondPic){
        string a1 = recursion(index1+1,index2,firstPic,secondPic);
        string a2 = recursion(in1,index2,firstPic,secondPic);
        string a3 = recursion(in1,index2,firstPic,secondPic);
        string a4 = recursion(in1,index2,firstPic,secondPic);
        if(a1 == a2 && a2 == a3 && a3 == a4 && (a4 == "1" || a4 == "0")){
            return a1;
        }
        else{
            a1 = CheckIfItsSingleDigitBinN(a1);
            a2 = CheckIfItsSingleDigitBinN(a2);
            a3 = CheckIfItsSingleDigitBinN(a3);
            a4 = CheckIfItsSingleDigitBinN(a4);
            return "0" + a1 + a2 + a3 + a4;
        }
    }
    else{
        if(tmp1[index1] == '1' && tmp1[index1+1] == '1'){
            in1 = index1 + 2;
            return recursion(in1,index2,false,true);
        }
        if(tmp2[index2] == '1' && tmp2[index2+1] == '1'){
            in2 = index2 + 2;
            return recursion(index1,in2,true,false);
        }
        if(tmp1[index1] == '1' && tmp1[index1+1] == '0'){
            recursion(index1,index2,false,true);
            return recursion(index1,index2,true,false);
        }
        if(tmp2[index2] == '1' && tmp2[index2+1] == '0'){
            in2 = index2 + 2;
            recursion(index1,in2,true,false);
            return recursion(index1,index2,false,true);
        }
        string a1 = recursion(index1+1,index2+1,firstPic,secondPic);
        string a2 = recursion(in1,in2,firstPic,secondPic);
        string a3 = recursion(in1,in2,firstPic,secondPic);
        string a4 = recursion(in1,in2,firstPic,secondPic);
        if(a1 == a2 && a2 == a3 && a3 == a4 && (a4 == "1" || a4 == "0")){
            return a1;
        }
        else{
            a1 = CheckIfItsSingleDigitBinN(a1);
            a2 = CheckIfItsSingleDigitBinN(a2);
            a3 = CheckIfItsSingleDigitBinN(a3);
            a4 = CheckIfItsSingleDigitBinN(a4);
            return "0" + a1 + a2 + a3 + a4;
        }
    }
}

string ConvertDecimalToBinary(int a){
    string tmp = "";
    while(a != 0){
        if(a%2!=0){
            tmp += '1';
        }
        else{
            tmp += '0';
        }
        a /= 2;
    }
    reverse(tmp.begin(),tmp.end());
    while(tmp.length() % 4 != 0 || tmp.length() < 4){
        tmp = "0" + tmp;
    }
    return tmp;
}

string ConvertHexaToBinary(string & st){
    string tmp = "";
    for(int i=0;i<st.length();i++){
        for(int j=0;j<16;j++){
            if(hexa[j] == st[i]){
                tmp += ConvertDecimalToBinary(j);
                break;
            }
        }
    }
    return tmp;
}

int FindFirstOne(string & tmp){
    for(int i=0;i<tmp.size();i++){
        if(tmp[i] == '1'){
            return i+1;
        }
    }
    return -1;
}


char getHexCharacter(string str) {
    if (str.compare("1111") == 0) return 'F';
    else if (str.compare("1110") == 0) return 'E';
    else if (str.compare("1101") == 0) return 'D';
    else if (str.compare("1100") == 0) return 'C';
    else if (str.compare("1011") == 0) return 'B';
    else if (str.compare("1010") == 0) return 'A';
    else if (str.compare("1001") == 0) return '9';
    else if (str.compare("1000") == 0) return '8';
    else if (str.compare("0111") == 0) return '7';
    else if (str.compare("0110") == 0) return '6';
    else if (str.compare("0101") == 0) return '5';
    else if (str.compare("0100") == 0) return '4';
    else if (str.compare("0011") == 0) return '3';
    else if (str.compare("0010") == 0) return '2';
    else if (str.compare("0001") == 0) return '1';
    else if (str.compare("0000") == 0) return '0';
}

string ConvertBinaryIntoHexa(string a){
    //block of 4 digits
    while(a.length() % 4 != 0 || a.length() < 4){
        a = "0" + a;
    }
    string result = "";
    for(int i =0;i<a.length()/4;i++){
        string tmp = "";
        for(int j=0;j<4;j++){
            tmp += a[i*4+j];
        }
        string s(1,getHexCharacter(tmp));
        result += s;
    }
    return result;
}

int main() {
    int cnt = 0;
    while(cin>>st1>>st2){
        if(st1=="0"){return 0;}
        cnt++;

        tmp1 = ConvertHexaToBinary(st1);
        tmp2 = ConvertHexaToBinary(st2);

        string binary = "1";
        string tmp = recursion(FindFirstOne(tmp1),FindFirstOne(tmp2),true,true);
        tmp = CheckIfItsSingleDigitBinN(tmp);
        binary += tmp;
        cout << "Image " << cnt << ":" << endl;
        cout << ConvertBinaryIntoHexa(binary) << endl;
        cout << endl;
    }
    return 0;
}