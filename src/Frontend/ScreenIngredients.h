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
    int Run(const map<string, string> & mapa, vector<string> &);
    int Run(){return 0;}
    void Run(string &, string &){};
    void KeyUp();
    void KeyDown();
    void KeyLeft(){};
    void KeyRight(){};
    void Backspace();
    void Enter();
    void OtherKey();
protected:
private:
    void RefreshWholeWindow(WINDOW *menu_win);
    void PrintTextInfoForUser() const;

    string ingredientSelectionString;
    int from,to,picked,selected;
    int ingridientBoxHeight,ingridientBoxWidth,ingridientStartx,ingridientStarty;
    int pickedIngridientsBoxHeight,pickedIngridientsBoxWidth,pickedIngridientsStartx,pickedIngridientsStarty;

    WINDOW *menu_win;
    WINDOW *menuWinPickedIngridients;

    bool userPressedDoubleEnter,finishSelection;

    vector<string> myPickedIngridients;
    vector<string> options;
    const map<string, string> * myMap;
};

#endif //RECIPE_MANAGER_SCREENINGREDIENTS_H
