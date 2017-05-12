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

#define SCREEN_LOGIN_MENU 0
#define SCREEN_LOGIN_PASSWORD 1
#define SCREEN_USER_MENU 2
#define SCREEN_INGREDIENTS 3
#define SCREEN_RECIPES 4
#define SCREEN_SINGLE_RECIPE 5


/// The main Frontend functions from which all Screens are created
void Frontend::Run(Connection &c, Data & data) {
    //variables---------------------------------------------------------------------------------------------------------
    Screen * screen = NULL;
    bool loggedIn=false;//,downloadedData=false;
    int userID=0,showOrCreateRecipe=0;
    string loginOrRegister="",login="",password="";
    vector<string> pickedIngredients;
    vector<string> recipeVector;// first it holds recommended recipe, then after recipe selection it holds string index
    //of selected recipe
    //------------------------------------------------------------------------------------------------------------------

    while(!loggedIn)
    {
        login="";password="";
        switchScreens(SCREEN_LOGIN_MENU,screen);
        int choice = screen->Run();
        if(choice==0)
        {
            switchScreens(SCREEN_LOGIN_PASSWORD,screen);
            screen->Run(login,password);
            loggedIn = c.Connect(login, password,userID);
        }
        else if(choice==1)
        {
            switchScreens(SCREEN_LOGIN_PASSWORD,screen);
            screen->Run(login,password);
            loggedIn = c.Register(login,password,userID);
        }
        else
        {
            return;
        }
    }

    data.UpdateScreenWidth(COLS);
    data.CreateNewUser(new User(userID,login));

    ProgressBar(&data,&Data::GetDataFromDatabase,18);
    //downloadedData=true;
    switchScreens(SCREEN_INGREDIENTS,screen);
    screen->AssignData(data);
    showOrCreateRecipe=screen->Run(data.GetMapOfIngridients(),pickedIngredients);

    if(showOrCreateRecipe){
        data.CreateRecipeBasedOnIngredientsSelected(pickedIngredients);
        string recommendedRecipe = data.GetRecommendedRecipe((*data.GetRecipe()),data.GetUser()->GetUserId());
        data.DeleteRecipeBasedOnIngredients();
        recipeVector.push_back(recommendedRecipe);
        switchScreens(SCREEN_RECIPES,screen);
        //TODO MAYBE?
        screen->Run(data.GetMapOfRecipes(),recipeVector);

        switchScreens(SCREEN_SINGLE_RECIPE,screen);
        screen->AssignData(data);
        screen->Run(map<string,string>(),recipeVector);

    }

    /// at the end of program delete Screen instances
    if(screen!=NULL)
        delete screen;
}

void Frontend::switchScreens(const int screenChoice,Screen *&currentScreen) {
    Screen *tmpScreen = currentScreen;
    switch (screenChoice)
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
        default:
            return;
    }
    if(tmpScreen!=NULL)
        delete tmpScreen;
}

/**
 * \return true if string exists in vector of string
 */
bool Frontend::Contain(const vector<string> &arr,const string &lookingFor) const {
    for(auto const &item : arr) {
        if(item==lookingFor)
        {
            return true;
        }
    }
    return false;
}

/// Variable to is used to determinate how many strings to show in WINDOW Box
void Frontend::AssignValueToVariableTo(int &to, const int &sizeOfVector, const int & boxSize) {
    if(sizeOfVector>(boxSize)-3)///TODO do not hardcode it
    {
        to=(boxSize)-3;
    }
    else
    {
        to=sizeOfVector;
    }
}

///shows progress given given task with n (parameter max) tasks to be done
template<class TRIDA>
void Frontend::ProgressBar(TRIDA *d,void (TRIDA::*function)(int),const int max)
{
    int outOf=25,before=0,percentage=0,y=1,x=1;
    string s="",percentageString="";
    int loginBoxWidth=25,loginBoxHeight=7;
    middleStartX = (COLS - loginBoxWidth) / 2;
    middleStartY = (LINES - loginBoxHeight) / 3;
    WINDOW *win = newwin(3, 25, middleStartY, middleStartX);

    clear();
    initscr();
    noecho();
    cbreak();

    mvprintw(middleStartY-1,middleStartX,"Downloading Data: ");
    attron(A_BOLD);
    mvprintw(middleStartY-1,middleStartX+18,"0%%");
    attroff(A_BOLD);
    box(win, 0, 0);

    refresh();
    wrefresh(win);
    for(int i=1;i<=max;i++)
    {
        outOf=25;
        (d->*function)(i);
        outOf=25*(i+1)/max;
        for(int j=0;j<outOf-before;j++)
        {
            s+='=';
        }
        wattron(win, A_STANDOUT);
        mvwprintw(win, y, x, "%s", s.c_str());
        wattroff(win, A_STANDOUT);
        before=outOf;

        percentage=outOf*4;
        percentageString = std::to_string(percentage);
        percentageString+="%%";
        attron(A_BOLD);
        mvprintw(middleStartY-1,middleStartX+18,percentageString.c_str());
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

Frontend::Frontend() {
}

Frontend::~Frontend() {

}