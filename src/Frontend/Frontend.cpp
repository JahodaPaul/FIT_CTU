//
// Created by pjahoda on 4/21/17.
//
#include "Frontend.h"
#include "Screen.h"
#include "ScreenLogin.h"
#include "ScreenLoginPassword.h"
#include "ScreenIngredients.h"
#include "ScreenRecipes.h"
#include "ScreenUserMenu.h"
#include "ScreenSingleRecipe.h"
#include "ScreenBeverages.h"

/// The main Frontend functions from which all Screens are created
void Frontend::Run(Connection &c, Data &data)
{
    //variables---------------------------------------------------------------------------------------------------------
    Screen *screen = NULL;
    bool loggedIn = false;
    downloadedData = false;
    userID = 0;
    showOrCreateRecipe = 0;
    screenChoiceMenu = 0;
    loginChoice = 0;
    loginOrRegister = "";
    login = "";
    password = "";
    recommendedRecipe = "";
    frontendData = &data;
    pickedIngredients.clear();
    beverages.clear(); //TODO download beverages from user menu into beverages
    recipeVector.clear();// first it holds recommended recipe, then after recipe selection it holds string index
    //of selected recipe
    //------------------------------------------------------------------------------------------------------------------

    while(!loggedIn)
    {
        SwitchScreens(SCREEN_LOGIN_MENU, screen);
        if(loginChoice == 0)
        {
            SwitchScreens(SCREEN_LOGIN_PASSWORD, screen);
            loggedIn = c.Connect(login, password, userID);
        }
        else if(loginChoice == 1)
        {
            SwitchScreens(SCREEN_LOGIN_PASSWORD, screen);
            loggedIn = c.Register(login, password, userID);
        }
        else
        {
            if(screen != NULL)
            {
                delete screen;
            }
            return;
        }
    }

    SwitchScreens(SCREEN_USER_MENU, screen);
    //SCREEN_INGREDIENTS is selected afterwards (currently no other option)

    // in this while Screens are changing until exit is selected
    while(1)
    {
        if(screenChoiceMenu == -2)
        {
            if(screen != NULL)
            {
                delete screen;
            }
            return;
        }
        else if(screenChoiceMenu != -1)
        {
            SwitchScreens(screenChoiceMenu, screen);
        }
        else
        {//just for testing purposes
            SwitchScreens(SCREEN_USER_MENU, screen);
        }
    }
}

///makes new instance of a class that inherits from Screen class and deletes the old one. Also calls RunScreen method
void Frontend::SwitchScreens(const int screenChoice, Screen *&currentScreen)
{
    Screen *tmpScreen = currentScreen;
    switch(screenChoice)
    {
        case SCREEN_LOGIN_MENU:
            currentScreen = new ScreenLogin();
            break;
        case SCREEN_USER_MENU:
            currentScreen = new ScreenUserMenu();
            break;
        case SCREEN_INGREDIENTS:
            currentScreen = new ScreenIngredients();
            break;
        case SCREEN_RECIPES:
            currentScreen = new ScreenRecipes();
            break;
        case SCREEN_LOGIN_PASSWORD:
            currentScreen = new ScreenLoginPassword();
            break;
        case SCREEN_SINGLE_RECIPE:
            currentScreen = new ScreenSingleRecipe();
            break;
        case SCREEN_BEVERAGES:
            currentScreen = new ScreenBeverages();
            break;
        default:
            return;
    }
    if(tmpScreen != NULL)
    {
        delete tmpScreen;
    }
    RunScreen(screenChoice, currentScreen);
}

/**
 * this function is called only from SwitchScreens function. It downloads/preprocesses data and then calls Run function
 * \param screenChoice  which screen is will be running
 * \param currentScreen current instance of a class which inherits from Screen class
 */
void Frontend::RunScreen(const int screenChoice, Screen *currentScreen)
{
    switch(screenChoice)
    {
        case SCREEN_LOGIN_MENU:
            loginChoice = currentScreen->Run();
            break;
        case SCREEN_USER_MENU:
            frontendData->UpdateScreenWidth(COLS);
            currentScreen->AssignData(*frontendData);
            if(!downloadedData)
            {
                frontendData->CreateNewUser(new User(userID, login));
                ProgressBar(frontendData, &DataSQL::GetDataFromDatabase, 18);
                downloadedData = true;
            }
            screenChoiceMenu = currentScreen->Run();
            break;
        case SCREEN_INGREDIENTS:
            currentScreen->AssignData(*frontendData);
            screenChoiceMenu = currentScreen->Run(frontendData->GetMapOfIngridients(), pickedIngredients);
            break;
        case SCREEN_RECIPES:
            frontendData->DeleteRecipeBasedOnIngredients();
            frontendData->CreateRecipeBasedOnIngredientsSelected(pickedIngredients);
            recommendedRecipe = frontendData->GetRecommendedRecipe((*frontendData->GetRecipe()), frontendData->GetUser()->GetUserId());
            frontendData->DeleteRecipeBasedOnIngredients();
            recipeVector.push_back(recommendedRecipe);
            screenChoiceMenu = currentScreen->Run(frontendData->GetMapOfRecipes(), recipeVector);
            break;
        case SCREEN_LOGIN_PASSWORD:
            currentScreen->Run(login, password);
            break;
        case SCREEN_SINGLE_RECIPE:
            currentScreen->AssignData(*frontendData);
            screenChoiceMenu = currentScreen->Run(map<string, string>(), recipeVector);
            if(screenChoiceMenu != SCREEN_SINGLE_RECIPE)
            {
                recipeVector.clear();
            }
            if(screenChoiceMenu != SCREEN_RECIPES && screenChoiceMenu != SCREEN_SINGLE_RECIPE)
            {
                pickedIngredients.clear();
            }
            break;
        case SCREEN_BEVERAGES:
            currentScreen->AssignData(*frontendData);
            screenChoiceMenu = currentScreen->Run(frontendData->GetMapOfBeverages(),beverages);
        default:
            return;
    }
}


/// Variable to is used to determinate how many strings to show in WINDOW Box
void Frontend::AssignValueToVariableTo(int &to, const int &sizeOfVector, const int &boxSize)
{
    if(sizeOfVector > (boxSize) - 3)///TODO do not hardcode it
    {
        to = (boxSize) - 3;
    }
    else
    {
        to = sizeOfVector;
    }
}

///shows progress given given task with n (parameter max) tasks to be done
template<class TRIDA, class TRIDA2>
void Frontend::ProgressBar(TRIDA *d, void (TRIDA2::*function)(int), const int max)
{
    int outOf = 25, before = 0, percentage = 0, y = 1, x = 1;
    string s = "", percentageString = "";
    int loginBoxWidth = 25, loginBoxHeight = 7;
    middleStartX = (COLS - loginBoxWidth) / 2;
    middleStartY = (LINES - loginBoxHeight) / 3;
    WINDOW * win = newwin(3, 25, middleStartY, middleStartX);

    clear();
    initscr();
    noecho();
    cbreak();

    mvprintw(middleStartY - 1, middleStartX, "Downloading Data: ");
    attron(A_BOLD);
    mvprintw(middleStartY - 1, middleStartX + 18, "0%%");
    attroff(A_BOLD);
    box(win, 0, 0);

    refresh();
    wrefresh(win);
    for(int i = 1; i <= max; i++)
    {
        outOf = 25;
        (d->*function)(i);
        outOf = 25 * (i + 1) / max;
        for(int j = 0; j < outOf - before; j++)
        {
            s += '=';
        }
        wattron(win, A_STANDOUT);
        mvwprintw(win, y, x, "%s", s.c_str());
        wattroff(win, A_STANDOUT);
        before = outOf;

        percentage = outOf * 4;
        percentageString = std::to_string(percentage);
        percentageString += "%%";
        attron(A_BOLD);
        mvprintw(middleStartY - 1, middleStartX + 18, percentageString.c_str());
        attroff(A_BOLD);

        refresh();
        wrefresh(win);
    }
    wrefresh(win);
    clrtoeol();
    refresh();
    endwin();
    system("clear");
}

Frontend::Frontend()
{
    frontendData = NULL;
}

Frontend::~Frontend()
{
}