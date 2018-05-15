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

    int Run(const map <string, string> &mapa, vector <string> &) { return 0; }

    void Run(string &, string &) {};

    void AssignData(Data &data) {};

    void KeyUp();

    void KeyDown();

    void KeyLeft() {};

    void KeyRight() {};

    void Backspace() {};

    void Enter();

    void OtherKey();

protected:
    void CountAverageStringSize(const vector <string> &vectorOfStrings, int &averageSize);

    vector <string> choices;
    vector <string> pictureVector;
    vector <string> vectorForThirdWindow;
    int averageStringSize, averageStringPicture;
    int firstWindowHeight, firstWindowWidth, firstWindowStartX, firstWindowStartY;
    int secondWindowHeight, secondWindowWidth, secondWindowStartX, secondWindowStartY;
    int thirdWindowHeight, thirdWindowWidth, thirdWindowStartX, thirdWindowStartY;
    int highlightThirdWindow;

    bool center;
    bool thirdWindowSelected;

    virtual void PrintStuff() const;

    virtual void SetVariables();

    void ChangeFocus();

private:
    WINDOW *menu_win;
    WINDOW *thirdWindow;
};

#endif //RECIPE_MANAGER_SCREENLOGIN_H
