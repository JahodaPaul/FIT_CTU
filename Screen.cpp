//
// Created by pjahoda on 5/3/17.
//

#include "Screen.h"

void Screen::PrintMenu(WINDOW *menu_win, const int highlight,const vector<string>& choices,const bool center,const int& boxWidth,const int& boxHeight,const int &averageStringSize,const int& from,const int& to)
{
    int x,y;
    if(center)
    {
        x=(boxWidth/2 - averageStringSize/2);
        y=(boxHeight/2 - (to/2));
    }
    else
    {
        x=2;
        y=1;
    }
    box(menu_win, 0, 0);
    for(int i = from; i < to; ++i)
    {
        if(highlight == i) // Highlight the present choice
        {
            wattron(menu_win, A_STANDOUT);
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
            wattroff(menu_win, A_STANDOUT);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
        y++;
    }
    wrefresh(menu_win);
}

void Screen::GetUserInfo(string &login, string &password) {
    cout << "login: ";
    cin >> login;
    cout << "password: ";
    cin >> password;
}

Screen::Screen() {

}