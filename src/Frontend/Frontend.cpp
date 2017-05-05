//
// Created by pjahoda on 4/21/17.
//
#include "Frontend.h"
#include "Screen.h"
#include "ScreenLogin.h"
#include "ScreenIngredients.h"

/// The main Frontend functions from which all Screens are created
void Frontend::Run(Connection &c,Data & data) {
    //variables---------------------------------------------------------------------------------------------------------
    Screen * loginScreen = new ScreenLogin();
    Screen * ingredientScreen = new ScreenIngredients();
    bool loggedIn=false;//,downloadedData=false;
    string loginOrRegister="",login="",password="";
    //------------------------------------------------------------------------------------------------------------------

    while(!loggedIn)
    {
        int choice = loginScreen->Run();
        if(choice==0)
        {
            loginScreen->GetUserInfo(login,password);
            loggedIn = c.Connect(login, password);
        }
        else if(choice==1)
        {
            loginScreen->GetUserInfo(login,password);
            loggedIn = c.Register(login,password);
        }
        else
        {
            return;
        }
    }

    ProgressBar(&data,&Data::GetDataFromDatabase,18);
    //downloadedData=true;
    ingredientScreen->Run(data.GetMapOfIngridients());


    /// at the end of program delete Screen instances
    delete loginScreen;
    delete ingredientScreen;
}

/**
 * \return true if string exists in vector of string
 */
bool Frontend::Contain(const vector<string> &arr, string lookingFor) {
    for(auto const &item : arr) {
        if(item==lookingFor)
        {
            return true;
        }
    }
    return false;
}

/// Variable to is used to determinate how many strings to show in WINDOW Box
void Frontend::AssignValueToVariableTo(int &to, const int &sizeOfVector) {
    if(sizeOfVector>(LINES-5)-3)///TODO do not hardcode it
    {
        to=(LINES-5)-3;
    }
    else
    {
        to=sizeOfVector;
    }
}

///shows progress given given task with n (parameter max) tasks to be done
template<class TRIDA>
void Frontend::ProgressBar(TRIDA *d,void (TRIDA::*function)(int),int max)
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
