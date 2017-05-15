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

#define SCREEN_LOGIN_MENU 0
#define SCREEN_LOGIN_PASSWORD 1
#define SCREEN_USER_MENU 2
#define SCREEN_INGREDIENTS 3
#define SCREEN_RECIPES 4
#define SCREEN_SINGLE_RECIPE 5

class Screen;

class Frontend
{
public:
    Frontend();

    ~Frontend();

    void Run(Connection &c, Data &data);

    void RunIngridientSelection(const map <string, string> &);

protected:
    template <class T>
    bool Contain(const vector <T> &arr, const T &lookingFor) const;

    void AssignValueToVariableTo(int &to, const int &sizeOfVector, const int &boxSize);

    template<class TRIDA>
    void ProgressBar(TRIDA *d, void (TRIDA::*function)(int), const int max);

    int middleStartX;
    int middleStartY;

private:
    void SwitchScreens(const int screenChoice, Screen *&currentScreen);
    void RunScreen(const int screenChoice, Screen * currentScreen);

    bool downloadedData;
    int userID;
    int showOrCreateRecipe;
    int screenChoiceMenu;
    int loginChoice;
    vector <string> pickedIngredients;
    vector <string> recipeVector;
    string loginOrRegister, login, password;
    string recommendedRecipe;
    bool recipesNotSelectedYet;

    Data * frontendData;
};

/**
 * \return true if string exists in vector of string
 */
template <class T>
bool Frontend::Contain(const vector <T> &arr, const T &lookingFor) const
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

#endif //RECIPE_MANAGER_FRONTEND_H