#include <iostream>
#include <stdlib.h>
#include "Connection.h"

int main() {
    string loginOrRegister="",login="",password="";
    Connection c;
    bool loggedIn=false;

    while(!loggedIn)
    {
        system("clear");
        cout << "To register press 0 and enter. To login press 1 and enter. To exit, type \"exit\"." << endl;
        cin >> loginOrRegister;
        if (loginOrRegister == "1") {
            cout << "login: ";
            cin >> login;
            cout << "password: ";
            cin >> password;
            loggedIn = c.Connect(login, password);
        }
        else if (loginOrRegister == "0") {
            cout << "login: ";
            cin >> login;
            cout << "password: ";
            cin >> password;
            loggedIn = c.Register(login,password);
        }
        else if(loginOrRegister=="exit"){
            return 0;
        }
    }

    return 0;
}