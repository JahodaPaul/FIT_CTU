//
// Created by pjahoda on 5/7/17.
//

#include "ScreenLoginPassword.h"

ScreenLoginPassword::ScreenLoginPassword() {

}

ScreenLoginPassword::~ScreenLoginPassword() {

}

/**
 * @param login
 * @param password
 * gets username nad password
 */
void ScreenLoginPassword::Run(string & login,string & password) {
    GetUserInputOneLine("login: ",login,false);
    GetUserInputOneLine("password: ",password,true);
}

/**
 * Shows box in the middle of the screen where user types input
 * \param toBeShown string which is placed before user typed input
 * @param get
 * @param getPassword
 */
void ScreenLoginPassword::GetUserInputOneLine(string toBeShown,string &get,const bool getPassword)
{
    //variables---------------------------------------------------------------------------------------------------------
    returnString="";
    this->toBeShown=toBeShown;
    highlight=10;
    this->getPassword=getPassword;
    shownToUser.clear();
    shownToUser.push_back(toBeShown);
    userPressedEnter=false;
    clear();
    initscr();
    noecho();
    cbreak();
    width=25;
    height=3;
    Frontend::middleStartX = (COLS - width) / 2;
    Frontend::middleStartY = (LINES - height) / 3;
    menu_win = newwin(height, width, middleStartY, middleStartX);
    //------------------------------------------------------------------------------------------------------------------

    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Press enter to confirm input.");
    refresh();
    PrintMenu(menu_win,highlight, shownToUser,true,width,height,20,0,(int)shownToUser.size());
    while(1)
    {
        key = wgetch(menu_win);
        ReactToUserInput(key);
        PrintMenu(menu_win,highlight, shownToUser,true,width,height,20,0,(int)shownToUser.size());
        if(userPressedEnter)
            break;
    }
    get=returnString;
    clrtoeol();
    refresh();
    endwin();
}

void ScreenLoginPassword::Backspace() {
    string temporaryString="";
    for(int i=0;i<(int)(returnString.length())-1;i++)
    {
        temporaryString+=returnString[i];
    }
    returnString=temporaryString;
    if(getPassword)
    {
        temporaryString="";
        for(int i=0;i<(int)(returnString.length())-1;i++)
        {
            temporaryString+='*';
        }
    }
    shownToUser[0]=toBeShown+temporaryString;
    menu_win = newwin(height, width, middleStartY, middleStartX);
    keypad(menu_win, TRUE);
    refresh();
}

void ScreenLoginPassword::Enter() {
    userPressedEnter=true;
}

void ScreenLoginPassword::OtherKey() {
    if((key>96 && key < 123) || (key > 64 && key < 91) || (key > 47 && key < 58))
    {
        shownToUser[0]+=char(key);
        returnString+=char(key);
        if(getPassword)
        {
            string temporaryString="";
            for(int i=0;i<(int)(returnString.length())-1;i++)
            {
                temporaryString+='*';
            }
            shownToUser[0]=toBeShown+temporaryString;
            shownToUser[0]+=(char)(key);
        }
        refresh();
    }
}