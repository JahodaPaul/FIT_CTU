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
    int Run(const map<string, string> & mapa){return 0;}
protected:
private:
    vector<string> choices;
    int averageStringSizeLogin;
    int loginStartx;
    int loginStarty;
    int loginBoxWidth;
    int loginBoxHeight;


};

#endif //RECIPE_MANAGER_SCREENLOGIN_H
