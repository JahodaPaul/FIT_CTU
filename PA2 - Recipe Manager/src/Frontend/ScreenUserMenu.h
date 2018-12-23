//
// Created by pjahoda on 5/7/17.
//

#ifndef RECIPE_MANAGER_SCREENUSERMENU_H
#define RECIPE_MANAGER_SCREENUSERMENU_H

#include "ScreenLogin.h"

class ScreenUserMenu : public ScreenLogin
{
public:
    ScreenUserMenu();

    ~ScreenUserMenu();

    int Run(const map <string, string> &mapa, vector <string> &) { return 0; }

    //int Run() { return 0; }

    void Run(string &, string &) {};

    void AssignData(Data &data);

    //void KeyUp() {};

    //void KeyDown() {};

    void KeyLeft();

    void KeyRight();

    void Backspace() {};

    void Enter();

    //void OtherKey() {};

    void PrintStuff() const;

    void SetVariables();

protected:
private:
    Data *myData;
};

#endif //RECIPE_MANAGER_SCREENUSERMENU_H
