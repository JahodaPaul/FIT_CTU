//
// Created by pjahoda on 4/21/17.
//



#ifndef RECIPE_MANAGER_FRONTEND_H
#define RECIPE_MANAGER_FRONTEND_H

#include "Screen.h"

class Frontend
{
public:
    Frontend();

    ~Frontend();

    void Run(Connection &c, Data &data);

protected:
private:
    template<class TRIDA, class TRIDA2>
    void ProgressBar(TRIDA *d, void (TRIDA2::*function)(int), const int max);

    void SwitchScreens(const int screenChoice, Screen *&currentScreen);

    void RunScreen(const int screenChoice, Screen *currentScreen);

    int middleStartX;
    int middleStartY;
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

    Data *frontendData;
};

#endif //RECIPE_MANAGER_FRONTEND_H