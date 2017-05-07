//
// Created by pjahoda on 5/7/17.
//

#ifndef RECIPE_MANAGER_SCREENRECIPES_H
#define RECIPE_MANAGER_SCREENRECIPES_H

#include "Screen.h"

class ScreenRecipes: public Screen
{
public:
    ScreenRecipes();
    ~ScreenRecipes();
    int Run(const map<string, string> & mapa, vector<string> &){return 0;}
    int Run(){return 0;}
protected:
private:
};

#endif //RECIPE_MANAGER_SCREENRECIPES_H
