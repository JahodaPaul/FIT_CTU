//
// Created by pjahoda on 5/3/17.
//

#include "ScreenLogin.h"

/**
 * Login screen which has three choices: login, register and exit
 * scrolling  is fully functional
 * \return selected choice: 0 for login, 1 for register and 2 for exit
 */
int ScreenLogin::Run() {
    //variables---------------------------------------------------------------------------------------------------------
    highlight=0;
    userPressedEnter=false;
    clear();
    initscr();
    noecho();
    cbreak();
    Frontend::middleStartX = (COLS - loginBoxWidth) / 2;
    Frontend::middleStartY = (LINES - loginBoxHeight) / 3;
    WINDOW *menu_win = newwin(loginBoxHeight, loginBoxWidth, middleStartY, middleStartX);
    //------------------------------------------------------------------------------------------------------------------

    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    PrintMenu(menu_win, highlight,choices,true,loginBoxWidth,loginBoxHeight,averageStringSizeLogin,0,(int)choices.size());
    while(1)
    {
        key = wgetch(menu_win);
        switch(key)
        {	case KEY_UP:
                if(highlight == 0)
                    highlight = (int)(choices.size()-1);
                else
                    highlight--;
                break;
            case KEY_DOWN:
                if(highlight == (int)(choices.size()-1))
                    highlight = 0;
                else
                    highlight++;
                break;
            case 10:
                userPressedEnter=true;
                break;
            default:
                refresh();
                break;
        }
        PrintMenu(menu_win, highlight,choices,true,loginBoxWidth,loginBoxHeight,averageStringSizeLogin,0,(int)choices.size());
        if(userPressedEnter)
            break;
    }
    clrtoeol();
    refresh();
    endwin();
    system("clear");
    return highlight;
}

/// sets login screen choices (login ect) and calculates averages string size of vector choices for better looking UI
ScreenLogin::ScreenLogin()
{
    loginBoxWidth=25;
    loginBoxHeight=7;
    choices.push_back("login");
    choices.push_back("register");
    choices.push_back("exit");
    averageStringSizeLogin=0;
    for(unsigned int i=0;i<choices.size();i++)
    {
        averageStringSizeLogin+=choices[i].length();
    }
    averageStringSizeLogin /= choices.size();
}

ScreenLogin::~ScreenLogin() {

}
