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
    virtual ~Screen(){}
    virtual int Run(){return 0;}
    virtual int Run(const map<string, string> & mapa,vector<string> &){return 0;}
    void GetUserInfo(string &login, string &password);

protected:
    int key;
    bool userPressedEnter;
    int highlight;
    void PrintMenu(WINDOW *menu_win, const int highlight,const vector<string>& choices,const bool center,const int& boxWidth,const int& boxHeight,const int &averageStringSize,const int& from,const int& to);
    void PrintUserTypedIngredient(string &,vector<string> &,bool newChar,const map<string,string> &,int &from,int &to,int &highlight,int &selected);
    template <class T>
    void OnlySelectedRangeOfStringsRemain(const T lowerbound,int &from,int &to,int &highlight,vector<string> &vectorOfStrings,const T higherbound, bool &changed);
    void OnlySelectedRangeOfStringsRemain(const unsigned int lowerbound,int &from,int &to,int &highlight,vector<string> &vectorOfStrings, const unsigned int higherbound, bool &changed);
    void GetUserInputOneLine(string toBeShown,string &get,const bool getPassword);

private:
};

#endif //RECIPE_MANAGER_SCREEN_H
