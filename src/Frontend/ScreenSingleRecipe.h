//
// Created by pjahoda on 5/12/17.
//

#ifndef RECIPE_MANAGER_SCREENSINGLERECIPE_H
#define RECIPE_MANAGER_SCREENSINGLERECIPE_H

#include "ScreenLogin.h"

class ScreenSingleRecipe : public ScreenLogin
{
public:
    ScreenSingleRecipe();

    ~ScreenSingleRecipe();

    int Run(const map <string, string> &mapa, vector <string> &);

    int Run() { return 0; }

    void Run(string &, string &) {};

    void AssignData(Data &data);

    //void KeyUp() {};

    //void KeyDown() {};

    void KeyLeft() {};

    void KeyRight() {};

    void Backspace() {};

    void Enter();

    //void OtherKey() {};

    void PrintStuff() const;

    void SetVariables();

    void RefreshLikedRecipes();

protected:
private:
    Data *myData;
    bool finishSelection;

    Recipe * singleRecipe;

};

#endif //RECIPE_MANAGER_SCREENSINGLERECIPE_H
