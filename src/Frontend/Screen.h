//
// Created by pjahoda on 5/3/17.
//

#ifndef RECIPE_MANAGER_SCREEN_H
#define RECIPE_MANAGER_SCREEN_H

#include "Frontend.h"

class Screen : public Frontend
{
public:
    Screen();

    virtual ~Screen();

    virtual int Run() { return 0; }

    virtual int Run(const map <string, string> &mapa, vector <string> &) { return 0; }

    virtual void Run(string &, string &) {};

    virtual void AssignData(Data &data) {};

    void ReactToUserInput(const int &key);

    virtual void KeyUp() {};

    virtual void KeyDown() {};

    virtual void KeyLeft() {};

    virtual void KeyRight() {};

    virtual void Backspace() {};

    virtual void Enter() {};

    virtual void OtherKey() {};

protected:
    int key;
    bool userPressedEnter;
    int highlight;

    void PrintMenu(WINDOW *menu_win, const int highlight, const vector <string> &choices, const bool center, const int &boxWidth,
                   const int &boxHeight, const int &averageStringSize, const int &from, const int &to);

    void
    PrintUserTypedIngredient(string &, vector <string> &, bool newChar, const map <string, string> &, int &from, int &to, int &highlight,
                             int &selected, const int &boxSize);

    template<class T>
    void OnlySelectedRangeOfStringsRemain(const T lowerbound, int &from, int &to, int &highlight, vector <string> &vectorOfStrings,
                                          const T higherbound, bool &changed, const int &boxSize);

    void
    OnlySelectedRangeOfStringsRemain(const unsigned int lowerbound, int &from, int &to, int &highlight, vector <string> &vectorOfStrings,
                                     const unsigned int higherbound, bool &changed, const int &boxSize);

private:
};

#endif //RECIPE_MANAGER_SCREEN_H
