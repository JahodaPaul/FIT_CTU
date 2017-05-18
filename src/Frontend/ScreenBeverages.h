//
// Created by pjahoda on 5/16/17.
//

#ifndef RECIPE_MANAGER_SCREENBEVERAGES_H
#define RECIPE_MANAGER_SCREENBEVERAGES_H

#include "ScreenIngredients.h"

class ScreenBeverages : public ScreenIngredients
{
public:
    ScreenBeverages();

    ~ScreenBeverages();

    //int Run(const map <string, string> &mapa, vector <string> &) { return 0; }

    int Run() { return 0; }

    void Run(string &, string &) {};

    //void AssignData(Data &data);

    //void KeyUp() {};

    //void KeyDown() {};

    void KeyLeft() {};

    void KeyRight() {};

    //void Backspace();

    void Enter();

    bool AreYouRecipeScreen() { return false; }

    void OtherKey() {};

    //void PrintStuff() const;

    //void SetVariables();

    void AssignData(Data &data);

protected:
private:
    Data *myData;
};

#endif //RECIPE_MANAGER_SCREENBEVERAGES_H
