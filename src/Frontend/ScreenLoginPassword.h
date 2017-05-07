//
// Created by pjahoda on 5/7/17.
//

#ifndef RECIPE_MANAGER_SCREENLOGINPASSWORD_H
#define RECIPE_MANAGER_SCREENLOGINPASSWORD_H

#include "Screen.h"

class ScreenLoginPassword : public Screen
{
public:
    ScreenLoginPassword();
    ~ScreenLoginPassword();
    int Run(const map<string, string> & mapa, vector<string> &){return 0;}
    int Run(){return 0;};
    void Run(string &, string &);
    void KeyUp(){};
    void KeyDown(){};
    void KeyLeft(){};
    void KeyRight(){};
    void Backspace();
    void Enter();
    void OtherKey();

protected:
private:
    void GetUserInputOneLine(string toBeShown,string &get,const bool getPassword);
    vector<string> shownToUser;
    string returnString;
    string toBeShown;
    bool getPassword;
    WINDOW * menu_win;
    int width;
    int height;
};

#endif //RECIPE_MANAGER_SCREENLOGINPASSWORD_H
