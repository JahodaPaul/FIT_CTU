#include <iostream>
#include "Connection.h"

int main() {
    string loginOrRegister="",login="",password="";
    Connection c;
    cout << "To register press 0 and enter, to login press 1 and enter" << endl;

    cin >> loginOrRegister;
    if(loginOrRegister=="1")
    {
        cout << "login: ";
        cin >> login;
        cout << "password: ";
        cin >> password;
        c.Connect(login,password);
    }
    else
    {

    }


    //c.Connect();
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}