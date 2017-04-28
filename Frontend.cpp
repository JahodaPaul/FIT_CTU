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
            //DELETE AND UNCOMMENT WHEN DONT TESTING
            loggedIn=true;
            //loggedIn = c.Connect(login, password);
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
    //UNCOMMENT WHEN DONE TESTING
    //data.GetDataFromDatabase();
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

//WHEN DONE TESTING WRITE CONST MAP
void Frontend::RunIngridientSelection(map<string, string> & mapa) {
    highlight=0;
    userPressedEnter=false;
    bool userPressedDoubleEnter=false;
    bool finishSelection=false;
    int from=0,to=0,picked=0;
    string ingredientSelectionString="",temporaryString;
    clear();
    initscr();
    noecho();
    cbreak();
    ingridientBoxHeight= LINES-5;
    ingridientBoxWidth=COLS-20;
    ingridientStartx = 0;
    ingridientStarty = LINES-ingridientBoxHeight;
    pickedIngridientsBoxHeight=ingridientBoxHeight;
    pickedIngridientsBoxWidth=COLS-ingridientBoxWidth-1;
    pickedIngridientsStartx=ingridientBoxWidth;
    pickedIngridientsStarty=ingridientStarty;
    WINDOW *menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
    WINDOW *menuWinPickedIngridients = newwin(pickedIngridientsBoxHeight,pickedIngridientsBoxWidth,pickedIngridientsStarty,pickedIngridientsStartx);
    vector<string> options;
    vector<string> pickedIngridients;
    for(auto const &pair : mapa) {
        options.push_back(pair.first);
    }
    //DELETE WHEN DONE TESTING
    options.push_back("Ananas");options.push_back("Jablko");options.push_back("Jahoda");options.push_back("Hruska");
    mapa.insert(make_pair("Ananas","Whatever"));mapa.insert(make_pair("Jablko","Whatever"));mapa.insert(make_pair("Jahoda","Whatever"));mapa.insert(make_pair("Hruska","Whatever"));
    //

    PrintTextInfoForUser();
    keypad(menu_win, TRUE);
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
    PrintMenu(menuWinPickedIngridients,-1,pickedIngridients,false,pickedIngridientsBoxWidth,pickedIngridientsBoxHeight,0,0,picked);
    while(1)
    {
        key = wgetch(menu_win);
        switch(key)
        {	case KEY_UP:
                userPressedEnter=false;
                if(highlight == 0) {
                    highlight = (int) (options.size() - 1);
                    int diff=to-from;
                    to=options.size();
                    from=to-diff;
                    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                    RefreshWholeWindow(menu_win);
                }
                else {
                    highlight--;
                    if(from>highlight) {
                        menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                        RefreshWholeWindow(menu_win);
                        from--;
                        to--;
                    }
                }
                break;
            case KEY_DOWN:
                userPressedEnter=false;
                if(highlight == (int)(options.size()-1)) {
                    highlight = 0;
                    int diff=to-from;
                    from=0;
                    to=diff;
                    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                    RefreshWholeWindow(menu_win);
                }
                else {
                    highlight++;
                    if(highlight==to) {
                        menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                        RefreshWholeWindow(menu_win);
                        from++;
                        to++;
                    }
                }
                break;
            case 10:
                ingredientSelectionString="";
                PrintUserTypedIngredient(ingredientSelectionString,options,false,mapa);
                if(userPressedEnter)
                {
                    userPressedDoubleEnter=true;
                    userPressedEnter=false;
                }
                else
                {
                    if(!Contain(pickedIngridients,options[highlight])) {
                        picked++;
                        pickedIngridients.push_back(options[highlight]);
                    }
                    PrintMenu(menuWinPickedIngridients,-1,pickedIngridients,false,pickedIngridientsBoxWidth,pickedIngridientsBoxHeight,0,0,picked);
                    userPressedEnter=true;
                }
                break;
            case KEY_BACKSPACE:
                temporaryString=ingredientSelectionString;
                for(int i=0;i<(int)(ingredientSelectionString.length())-1;i++)
                {
                    temporaryString+=ingredientSelectionString[i];
                }
                ingredientSelectionString=temporaryString;
                PrintUserTypedIngredient(ingredientSelectionString,options,false,mapa);
                userPressedEnter=false;
                if(userPressedEnter)
                {
                    finishSelection=true;
                }
                break;
            default:
                ingredientSelectionString+=(char)key;
                PrintUserTypedIngredient(ingredientSelectionString,options,true,mapa);
                userPressedEnter=false;
                refresh();
                break;
        }
        PrintMenu(menu_win, highlight,options,false,ingridientBoxWidth,ingridientBoxHeight,0,from,to);
        if(finishSelection)
            break;
    }
    clrtoeol();
    refresh();
    endwin();
    system("clear");
    if(userPressedDoubleEnter)
    {
        //TODO
    }
    //return highlight;

}

void Frontend::RefreshWholeWindow(WINDOW *menu_win) {
    keypad(menu_win, TRUE);
    PrintTextInfoForUser();
    refresh();
}

bool Frontend::Contain(const vector<string> &arr, string lookingFor) {
    for(auto const &item : arr) {
        if(item==lookingFor)
        {
            return true;
        }
    }
    return false;
}

void Frontend::PrintTextInfoForUser() {
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    mvprintw(1,0,"Press double enter to Search for recipes containing chosen ingridients.");
    mvprintw(2,0,"Press enter and backspace to exit the application.");
    string s="";
    for(int i=0;i<COLS;i++)
    {
        s+='-';
    }
    mvprintw(3,0,s.c_str());
}

void Frontend::PrintUserTypedIngredient(string &s,vector<string>& arr,bool newChar,const map<string,string>& myMap) {
    unsigned int wordLenght = s.length();
    attron(A_BOLD);
    mvprintw(4, 0, s.c_str());
    attroff(A_BOLD);
    if(newChar)
    {
        for(auto const &word:arr)
        {
            
        }
    }
    else{

    }
}
