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
    void AssignData(Data & data){myData=&data;};

    void KeyUp();
    void KeyDown();
    void KeyLeft(){};
    void KeyRight(){};
    void Backspace();
    void Enter();
    void OtherKey();
protected:
    int firstWindowHeight,firstWindowWidth,firstWindowStartX,firstWindowStartY;
    int secondWindowHeight,secondWindowWidth,secondWindowStartX,secondWindowStartY;

    void RefreshWholeWindow(WINDOW *menu_win);
    virtual void PrintTextInfoForUser() const;

    string ingredientSelectionString;
    int from,to,picked,selected;


    WINDOW *menu_win;
    WINDOW *menuWinPickedIngridients;

    bool userPressedDoubleEnter,finishSelection;

    vector<string> myPickedIngridients;
    vector<string> options;
    const map<string, string> * myMap;
private:
    Data * myData;
};

#endif //RECIPE_MANAGER_SCREENINGREDIENTS_H
