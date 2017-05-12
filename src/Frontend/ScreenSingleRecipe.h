//
// Created by pjahoda on 5/12/17.
//

#ifndef RECIPE_MANAGER_SCREENSINGLERECIPE_H
#define RECIPE_MANAGER_SCREENSINGLERECIPE_H

#include "Screen.h"

class ScreenSingleRecipe : public Screen
{
public:
    ScreenSingleRecipe();
    ~ScreenSingleRecipe();
    int Run(const map<string, string> & mapa, vector<string> &);
    int Run(){return 0;}
    void Run(string &, string &){};
    void AssignData(Data & data);
    void KeyUp(){};
    void KeyDown(){};
    void KeyLeft(){};
    void KeyRight(){};
    void Backspace(){};
    void Enter();
    void OtherKey(){};
protected:
private:
    Data * myData;
    bool finishSelection;
};

#endif //RECIPE_MANAGER_SCREENSINGLERECIPE_H
