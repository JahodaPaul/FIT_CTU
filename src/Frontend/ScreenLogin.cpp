//
// Created by pjahoda on 5/3/17.
//

#include "ScreenLogin.h"

/**
 * Login screen which has three choices: login, register and exit
 * scrolling  is fully functional
 * \return selected choice: 0 for login, 1 for register and 2 for exit
 */
int ScreenLogin::Run()
{
    //variables---------------------------------------------------------------------------------------------------------
    highlight = 0;
    userPressedEnter = false;
    clear();
    initscr();
    start_color();// makes it a little bit brighter
    noecho();
    cbreak();
    SetVariables();
    menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
    WINDOW * secondWindow = newwin(secondWindowHeight,secondWindowWidth,secondWindowStartY,secondWindowStartX);
    thirdWindow = newwin(thirdWindowHeight, thirdWindowWidth, thirdWindowStartY, thirdWindowStartX);
    //------------------------------------------------------------------------------------------------------------------

    keypad(menu_win, TRUE);
    PrintStuff();
    refresh();
    PrintMenu(secondWindow,-1,pictureVector,true,secondWindowWidth,secondWindowHeight,averageStringPicture,0,(int)pictureVector.size());
    PrintMenu(thirdWindow,-1,vectorForThirdWindow,false,thirdWindowWidth,thirdWindowHeight,0,0,(int)vectorForThirdWindow.size());
    PrintMenu(menu_win, highlight, choices, center, firstWindowWidth, firstWindowHeight, averageStringSize, 0, (int) choices.size());
    while(1)
    {
        key = wgetch(menu_win);
        ReactToUserInput(key);
        if(!thirdWindowSelected)
        {
            PrintMenu(menu_win, highlight, choices, center, firstWindowWidth, firstWindowHeight, averageStringSize, 0, (int) choices.size());
        }
        else
        {
            PrintMenu(thirdWindow, highlightThirdWindow, vectorForThirdWindow, center, thirdWindowWidth, thirdWindowHeight, averageStringSize, 0, (int) vectorForThirdWindow.size());
        }
        if(userPressedEnter)
        {
            break;
        }
    }
    clrtoeol();
    refresh();
    endwin();
    system("clear");
    return highlight;
}

void ScreenLogin::SetVariables()
{
    firstWindowStartX = (COLS - firstWindowWidth) / 2;
    firstWindowStartY = (LINES - firstWindowHeight) / 3;
    secondWindowStartY=-1;
    secondWindowStartX=-1;
    secondWindowWidth=1;
    secondWindowHeight=1;
}

void ScreenLogin::PrintStuff() const
{
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
}

void ScreenLogin::KeyUp()
{
    if(!thirdWindowSelected)
    {
        if(highlight == 0)
        {
            highlight = (int) (choices.size() - 1);
        }
        else
        {
            highlight--;
        }
    }
    else
    {
        if(highlightThirdWindow == 0)
        {
            highlightThirdWindow = (int) (vectorForThirdWindow.size() - 1);
        }
        else
        {
            highlightThirdWindow--;
        }
    }
}

void ScreenLogin::KeyDown()
{
    if(!thirdWindowSelected)
    {
        if(highlight == (int) (choices.size() - 1))
        {
            highlight = 0;
        }
        else
        {
            highlight++;
        }
    }
    else
    {
        if(highlightThirdWindow == (int) (vectorForThirdWindow.size() - 1))
        {
            highlightThirdWindow = 0;
        }
        else
        {
            highlightThirdWindow++;
        }
    }
}

void ScreenLogin::Enter()
{
    userPressedEnter = true;
}

void ScreenLogin::OtherKey()
{
    refresh();
}

void ScreenLogin::ChangeFocus()
{
    if(vectorForThirdWindow.size() != 0)
    {
        thirdWindowSelected = !thirdWindowSelected;
    }
    if(thirdWindowSelected)
    {
        highlight=-1;
        highlightThirdWindow=0;
        PrintMenu(menu_win, highlight, choices, center, firstWindowWidth, firstWindowHeight, averageStringSize, 0, (int) choices.size());
    }
    else
    {
        highlightThirdWindow=-1;
        highlight=0;
        PrintMenu(thirdWindow, highlightThirdWindow, vectorForThirdWindow, center, thirdWindowWidth, thirdWindowHeight, averageStringSize, 0, (int) vectorForThirdWindow.size());
    }
}

/// counts average length of a string in vector
void ScreenLogin::CountAverageStringSize(const vector <string> &vectorOfStrings, int &averageSize)
{
    averageSize = 0;
    for(unsigned int i = 0; i < vectorOfStrings.size(); ++i)
    {
        averageSize += vectorOfStrings[i].length();
    }
    averageSize /= vectorOfStrings.size();
}

/// sets login screen choices (login ect) and calculates averages string size of vector choices for better looking UI
ScreenLogin::ScreenLogin()
{
    firstWindowWidth = 25;
    firstWindowHeight = 7;
    firstWindowStartY=0;
    firstWindowStartX=COLS-25;
    thirdWindowStartY=-1;
    thirdWindowStartX=-1;
    thirdWindowWidth=1;
    thirdWindowHeight=1;
    averageStringPicture=0;
    choices.push_back("login");
    choices.push_back("register");
    choices.push_back("exit");
    CountAverageStringSize(choices,averageStringSize);
    center=true;
    thirdWindowSelected=false;
    highlightThirdWindow=-1;
}

ScreenLogin::~ScreenLogin()
{

}
