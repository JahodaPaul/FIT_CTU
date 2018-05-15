//
// Created by pjahoda on 5/3/17.
//

#ifndef RECIPE_MANAGER_SCREEN_H
#define RECIPE_MANAGER_SCREEN_H

#include "../Backend/Connection.h"
#include "../Backend/Data.h"
#include "../../lib/curses/ncurses.h"
#include <iostream>
#include <string>

#define SCREEN_LOGIN_MENU 0
#define SCREEN_LOGIN_PASSWORD 1
#define SCREEN_USER_MENU 2
#define SCREEN_INGREDIENTS 3
#define SCREEN_RECIPES 4
#define SCREEN_SINGLE_RECIPE 5
#define SCREEN_BEVERAGES 6

class Screen
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
    int middleStartX;
    int middleStartY;

    template<class T>
    bool Contain(const vector <T> &arr, const T &lookingFor) const;

    void AssignValueToVariableTo(int &to, const int &sizeOfVector, const int &boxSize);

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

/**
 * \return true if string exists in vector of string
 */
template<class T>
bool Screen::Contain(const vector <T> &arr, const T &lookingFor) const
{
    for(auto const &item : arr)
    {
        if(item == lookingFor)
        {
            return true;
        }
    }
    return false;
}

#endif //RECIPE_MANAGER_SCREEN_H
