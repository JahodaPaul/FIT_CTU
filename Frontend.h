//
// Created by pjahoda on 4/21/17.
//

#ifndef RECIPE_MANAGER_FRONTEND_H
#define RECIPE_MANAGER_FRONTEND_H

#include "Connection.h"
#include "Data.h"
#include "Colormode.h"
Modifier red(FG_RED);
Modifier green(FG_GREEN);
Modifier blue(FG_BLUE);
Modifier def(FG_DEFAULT);

class Frontend
{
public:
    Frontend();
    void Run(Connection & c, Data & data);
protected:
private:
    int counter;
    void PrintRegisterLoginOrExist(int );
    void print_menu(WINDOW *menu_win, int highlight);
    int startx;
    int starty;
};

#endif //RECIPE_MANAGER_FRONTEND_H
