//
// Created by pjahoda on 4/21/17.
//



#ifndef RECIPE_MANAGER_FRONTEND_H
#define RECIPE_MANAGER_FRONTEND_H

#include "../Backend/Connection.h"
#include "../Backend/Data.h"
#include "../../lib/curses/ncurses.h"
#include <iostream>
#include <string>

class Screen;

class Frontend
{
public:
    Frontend();

    ~Frontend();

    void Run(Connection &c, Data &data);

    void RunIngridientSelection(const map <string, string> &);

protected:
    bool Contain(const vector <string> &arr, const string &lookingFor) const;

    void AssignValueToVariableTo(int &to, const int &sizeOfVector, const int &boxSize);

    template<class TRIDA>
    void ProgressBar(TRIDA *d, void (TRIDA::*function)(int), const int max);

    int middleStartX;
    int middleStartY;

private:
    void switchScreens(const int screenChoice, Screen *&currentScreen);

};

#endif //RECIPE_MANAGER_FRONTEND_H