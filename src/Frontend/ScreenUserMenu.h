//
// Created by pjahoda on 5/7/17.
//

#ifndef RECIPE_MANAGER_SCREENUSERMENU_H
#define RECIPE_MANAGER_SCREENUSERMENU_H

#include "Screen.h"

class ScreenUserMenu: public Screen
{
public:
    ScreenUserMenu();
    ~ScreenUserMenu();
    int Run(const map<string, string> & mapa, vector<string> &){return 0;}
    int Run(){return 0;}
protected:
private:

};

#endif //RECIPE_MANAGER_SCREENUSERMENU_H
