//
// Created by pjahoda on 4/21/17.
//
#include "Frontend.h"


void Frontend::Run(Connection &c,Data & data) {
    bool loggedIn=false;
    string loginOrRegister="",login="",password="";
    while(!loggedIn)
    {
        int choice = RunLogin();
        if(choice==0)
        {
            cout << "login: ";
            cin >> login;
            cout << "password: ";
            cin >> password;
            loggedIn = c.Connect(login, password);
        }
        else if(choice==1)
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
    RunIngridientSelection(data.GetMapOfIngridients());

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

void Frontend::PrintMenu(WINDOW *menu_win, const int highlight,const vector<string>& choices,const bool center,const int& boxWidth,const int& boxHeight,const int &averageStringSize,const int& from,const int& to)
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
        {	wattron(menu_win, A_STANDOUT);
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
            wattroff(menu_win, A_STANDOUT);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
        y++;
    }
    wrefresh(menu_win);
}

Frontend::~Frontend() {

}

int Frontend::RunLogin() {
    highlight=0;
    userPressedEnter=false;
    clear();
    initscr();
    noecho();
    cbreak();
    loginStartx = (COLS - loginBoxWidth) / 2;
    loginStarty = (LINES - loginBoxHeight) / 3;
    WINDOW *menu_win = newwin(loginBoxHeight, loginBoxWidth, loginStarty, loginStartx);

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

void Frontend::RunIngridientSelection(const map<string, string> & mapa) {
    highlight=0;
    userPressedEnter=false;
    int from=0,to=0;
    clear();
    initscr();
    noecho();
    cbreak();
    ingridientBoxHeight= LINES-2;
    ingridientBoxWidth=COLS-20;
    ingridientStartx = 0;
    ingridientStarty = LINES-ingridientBoxHeight;
    WINDOW *menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
    vector<string> options;
    for(auto const &pair : mapa) {
        options.push_back(pair.first);
    }
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    if((int)options.size()>ingridientBoxHeight-3)
    {
        to=ingridientBoxHeight-3;
    }
    else
    {
        to=(int)options.size();
    }
    PrintMenu(menu_win, highlight,options,false,ingridientBoxWidth,ingridientBoxHeight,0,from,to);
    while(1)
    {
        key = wgetch(menu_win);
        switch(key)
        {	case KEY_UP:
                if(highlight == 0) {
                    highlight = (int) (options.size() - 1);
                    int diff=to-from;
                    to=options.size();
                    from=to-diff;
                    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                    keypad(menu_win, TRUE);
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
                    refresh();
                }
                else {
                    highlight--;
                    if(from>highlight) {
                        menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                        keypad(menu_win, TRUE);
                        mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
                        refresh();
                        from--;
                        to--;
                    }
                }
                break;
            case KEY_DOWN:
                if(highlight == (int)(options.size()-1)) {
                    highlight = 0;
                    int diff=to-from;
                    from=0;
                    to=diff;
                    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                    keypad(menu_win, TRUE);
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
                    refresh();
                }
                else {
                    highlight++;
                    if(highlight==to) {
                        menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                        keypad(menu_win, TRUE);
                        mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
                        refresh();
                        from++;
                        to++;
                    }
                }
                break;
            case 10:
                userPressedEnter=true;
                break;
            default:
                refresh();
                break;
        }
        PrintMenu(menu_win, highlight,options,false,ingridientBoxWidth,ingridientBoxHeight,0,from,to);
        if(userPressedEnter)
            break;
    }
    clrtoeol();
    refresh();
    endwin();
    system("clear");
    //return highlight;

}
