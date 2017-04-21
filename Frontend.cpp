//
// Created by pjahoda on 4/21/17.
//
#include <iostream>
#include <string>

#include "Frontend.h"

void Frontend::Run(Connection &c,Data & data) {
    bool loggedIn=false;
    string loginOrRegister="",login="",password="";
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
            return;
        }
    }

    data.GetDataFromDatabase();

}
