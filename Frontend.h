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
    void RunIngridientSelection(const map<string,string>&);
protected:
    void RefreshWholeWindow(WINDOW *menu_win);
    bool Contain(const vector<string>& arr, string lookingFor);
    void PrintUserTypedIngredient(string &,vector<string> &,bool newChar,const map<string,string> &,int &from,int &to,int &highlight,int &selected);
    void AssignValueToVariableTo(int &to,const int &sizeOfVector);
    template <class T>
    void OnlySelectedRangeOfStringsRemain(T lowerbound,int &from,int &to,int &highlight,vector<string> &vectorOfStrings,T higherbound, bool &changed);
    void OnlySelectedRangeOfStringsRemain(unsigned int lowerbound,int &from,int &to,int &highlight,vector<string> &vectorOfStrings, unsigned int higherbound, bool &changed);
    template <class TRIDA>
    void ProgressBar(TRIDA *d,void (TRIDA::*function)(int),int max);

    int middleStartX;
    int middleStartY;
private:

};

#endif //RECIPE_MANAGER_FRONTEND_H