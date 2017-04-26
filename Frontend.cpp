//
// Created by pjahoda on 4/21/17.
//
#include "Frontend.h"


void Frontend::Run(Connection &c,Data & data) {
    bool loggedIn=false;
    string loginOrRegister="",login="",password="";
    while(!loggedIn)
    {
        highlight=0;
        userPressedEnter=false;
        clear();
        initscr();
        noecho();
        cbreak();
        loginStartx = (COLS - loginBoxWidth) / 2;
        loginStarty = (LINES - loginBoxHeight) / 2;
        WINDOW *menu_win = newwin(loginBoxHeight, loginBoxWidth, loginStarty, loginStartx);


        keypad(menu_win, TRUE);
        mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
        refresh();
        PrintMenu(menu_win, highlight,choices,true,loginBoxWidth,loginBoxHeight,averageStringSizeLogin);
        while(1)
        {	key = wgetch(menu_win);
            switch(key)
            {	case KEY_UP:
                    if(highlight == 0)
                        highlight = 2;
                    else
                        --highlight;
                    break;
                case KEY_DOWN:
                    if(highlight == 2)
                        highlight = 0;
                    else
                        ++highlight;
                    break;
                case 10:
                    userPressedEnter=true;
                    break;
                default:
                    refresh();
                    break;
            }
            PrintMenu(menu_win, highlight,choices,true,loginBoxWidth,loginBoxHeight,averageStringSizeLogin);
            if(userPressedEnter)
                break;
        }
        clrtoeol();
        refresh();
        endwin();
        system("clear");
        if(highlight==0)
            {
                cout << "login: ";
                cin >> login;
                cout << "password: ";
                cin >> password;
                loggedIn = c.Connect(login, password);
            }
            else if(highlight==1)
            {
                cout << "login: ";
                cin >> login;
                cout << "password: ";
                cin >> password;
                loggedIn = c.Register(login,password);
            }
            else
            {
                return;
            }
    }

    data.GetDataFromDatabase();

}

Frontend::Frontend() {
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

void Frontend::PrintMenu(WINDOW *menu_win, const int highlight,const vector<string>& choices,const bool center,const int& boxWidth,const int& boxHeight,const int &averageStringSize)
{
    int x,y;
    int size=(int)choices.size();
    if(center)
    {
        x=(boxWidth/2 - averageStringSize/2);
        y=(boxHeight/2 - (size/2));
    }
    else
    {
        x=1;
        y=1;
    }
    box(menu_win, 0, 0);
    for(int i = 0; i < size; ++i)
    {
        if(highlight == i) // Highlight the present choice
        {	wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
        y++;
    }
    wrefresh(menu_win);
}

Frontend::~Frontend() {

}
