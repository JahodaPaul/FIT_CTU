//
// Created by pjahoda on 5/3/17.
//

#ifndef RECIPE_MANAGER_SCREENLOGIN_H
#define RECIPE_MANAGER_SCREENLOGIN_H

#include "Screen.h"

class ScreenLogin : public Screen
{

public:
    ScreenLogin();
    ~ScreenLogin();
    int Run();
    int Run(const map<string, string> & mapa, vector<string> &){return 0;}
protected:
private:
    /// \property login screen choices - login, register, exit
    vector<string> choices;

    int averageStringSizeLogin;
    int loginStartx;
    int loginStarty;
    int loginBoxWidth;
    int loginBoxHeight;


};

#endif //RECIPE_MANAGER_SCREENLOGIN_H
