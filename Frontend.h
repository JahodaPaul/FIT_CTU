//
// Created by pjahoda on 4/21/17.
//

#ifndef RECIPE_MANAGER_FRONTEND_H
#define RECIPE_MANAGER_FRONTEND_H

#include "Connection.h"
#include "Data.h"
#include "Colormode.h"
#include "curses/ncurses.h"
#include <iostream>
#include <string>
//Modifier red(FG_RED);
//Modifier green(FG_GREEN);
//Modifier blue(FG_BLUE);
//Modifier def(FG_DEFAULT);

class Frontend
{
public:
    Frontend();
    ~Frontend();
    void Run(Connection & c, Data & data);
protected:
private:
    int counter;
    void PrintRegisterLoginOrExist(int );
    void PrintMenu(WINDOW *menu_win, const int highlight,const vector<string>& choices,const bool center,const int& boxWidth,const int& boxHeight,const int &);
    int loginStartx;
    int loginStarty;
    int loginBoxWidth;
    int loginBoxHeight;
    vector<string> choices;
    int highlight;
    bool userPressedEnter;
    int key;
    int averageStringSizeLogin;
};

#endif //RECIPE_MANAGER_FRONTEND_H
