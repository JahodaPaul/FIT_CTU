//
// Created by pjahoda on 5/3/17.
//

#ifndef RECIPE_MANAGER_SCREENINGREDIENTS_H
#define RECIPE_MANAGER_SCREENINGREDIENTS_H

#include "Screen.h"

class ScreenIngredients : public Screen
{
public:
    ScreenIngredients();
    ~ScreenIngredients();
    int Run(const map<string, string> & mapa);
    int Run(){return 0;}
protected:
private:
    void RefreshWholeWindow(WINDOW *menu_win);
    void PrintTextInfoForUser() const;
};

#endif //RECIPE_MANAGER_SCREENINGREDIENTS_H
