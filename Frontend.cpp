//
// Created by pjahoda on 4/21/17.
//
#include <iostream>
#include <string>
#include "curses/ncurses.h"

#include "Frontend.h"


#define WIDTH 25
#define HEIGHT 8

string choices[3] = {"Login", "Register", "Exit",};
int n_choices = 3;

void Frontend::Run(Connection &c,Data & data) {
    bool loggedIn=false;
    string loginOrRegister="",login="",password="";
    while(!loggedIn)
    {
        WINDOW *menu_win;
        int highlight = 1;
        int choice = 0;
        int key;

        initscr();
        clear();
        noecho();
        cbreak();	/* Line buffering disabled. pass on everything */
        startx = (COLS - WIDTH) / 2;
        starty = (LINES - HEIGHT) / 2;

        menu_win = newwin(HEIGHT, WIDTH, starty, startx);
        keypad(menu_win, TRUE);
        mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
        refresh();
        print_menu(menu_win, highlight);
        while(1)
        {	key = wgetch(menu_win);
            switch(key)
            {	case KEY_UP:
                    if(highlight == 1)
                        highlight = n_choices;
                    else
                        --highlight;
                    break;
                case KEY_DOWN:
                    if(highlight == n_choices)
                        highlight = 1;
                    else
                        ++highlight;
                    break;
                case 10:
                    choice = highlight;
                    break;
                default:
                    refresh();
                    break;
            }
            print_menu(menu_win, highlight);
            if(choice != 0)	/* User did a choice come out of the infinite loop */
                break;
        }
        clrtoeol();
        refresh();
        endwin();
        system("clear");
        if(choice==1)
            {
                cout << "login: ";
                cin >> login;
                cout << "password: ";
                cin >> password;
                loggedIn = c.Connect(login, password);
            }
            else if(choice==2)
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
    startx = 0;
    starty = 0;
}

void Frontend::print_menu(WINDOW *menu_win, int highlight)
{
    int x = 2;
    int y = 2;
    box(menu_win, 0, 0);
    for(int i = 0; i < n_choices; ++i)
    {	if(highlight == i + 1) /* High light the present choice */
        {	wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
        ++y;
    }
    wrefresh(menu_win);
}