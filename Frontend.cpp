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
    //variables---------------------------------------------------------------------------------------------------------
    highlight=0;
    userPressedEnter=false;
    clear();
    initscr();
    noecho();
    cbreak();
    loginStartx = (COLS - loginBoxWidth) / 2;
    loginStarty = (LINES - loginBoxHeight) / 3;
    WINDOW *menu_win = newwin(loginBoxHeight, loginBoxWidth, loginStarty, loginStartx);
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

void Frontend::RunIngridientSelection(const map<string, string> & mapa) {
    //variables---------------------------------------------------------------------------------------------------------
    highlight=0;
    userPressedEnter=false;
    bool userPressedDoubleEnter=false,finishSelection=false;//,typedSomething=false,refreshMenu=false;
    int from=0,to=0,picked=0,selected=0;
    string ingredientSelectionString="",temporaryString;
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
    //------------------------------------------------------------------------------------------------------------------

    clear();
    initscr();
    noecho();
    cbreak();

    for(auto const &pair : mapa) {
        options.push_back(pair.first);
    }

    PrintTextInfoForUser();
    keypad(menu_win, TRUE);
    refresh();
    AssignValueToVariableTo(to,(int)options.size());
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
                PrintUserTypedIngredient(ingredientSelectionString,options,false,mapa,from,to,highlight,selected);
                menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                RefreshWholeWindow(menu_win);
                if(userPressedEnter)
                {
                    userPressedDoubleEnter=true;
                    userPressedEnter=false;
                }
                else
                {
                    if(!Contain(pickedIngridients,options[selected])) {
                        picked++;
                        pickedIngridients.push_back(options[selected]);
                    }
                    PrintMenu(menuWinPickedIngridients,-1,pickedIngridients,false,pickedIngridientsBoxWidth,pickedIngridientsBoxHeight,0,0,picked);
                    userPressedEnter=true;
                }
                break;
            case KEY_BACKSPACE:
                temporaryString="";
                for(int i=0;i<(int)(ingredientSelectionString.length())-1;i++)
                {
                    temporaryString+=ingredientSelectionString[i];
                }
                ingredientSelectionString=temporaryString;
                PrintUserTypedIngredient(ingredientSelectionString,options,false,mapa,from,to,highlight,selected);
                menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                RefreshWholeWindow(menu_win);
                userPressedEnter=false;
                if(userPressedEnter)
                {
                    finishSelection=true;
                }
                break;
            default:
                ingredientSelectionString+=(char)key;
                PrintUserTypedIngredient(ingredientSelectionString,options,true,mapa,from,to,highlight,selected);
                menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                RefreshWholeWindow(menu_win);
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

void Frontend::PrintUserTypedIngredient(string &s,vector<string>& arr,bool newChar,const map<string,string>& myMap,int &from, int &to,int &highlight,int &selected) {
    unsigned int wordLenght = s.length();
    bool found=false;
    bool changed=false;
    if(newChar)
    {
        //user typed new Character--------------------------------------------------------------------------------------
        unsigned int index=wordLenght-1;
        if(wordLenght==1)
        {
            char tmp=toupper(s[index]);
            s=tmp;
        }
        else
        {
            char tmp=tolower(s[index]);
            string tmpString="";
            for(unsigned int i =0;i<index;i++)
            {
                tmpString+=s[i];
            }
            tmpString+=tmp;
            s=tmpString;
        }
        attron(A_BOLD);
        mvprintw(4, 0, s.c_str());
        attroff(A_BOLD);

        unsigned int lowerBound=0;
        for(unsigned int i=0;i<arr.size();i++)
        {
            if(found)
            {
                if(arr[i].length() < wordLenght)
                {
                    OnlySelectedRangeOfStringsRemain(lowerBound,from,to,highlight,arr,i,changed);
                    break;
                }
                if(s[index]!=arr[i][index])
                {
                    OnlySelectedRangeOfStringsRemain(lowerBound,from,to,highlight,arr,i,changed);
                    break;
                }
            }
            else if(arr[i].length() >= wordLenght)
            {
                if(s[index]==arr[i][index])
                {
                    found=true;
                    lowerBound=i;
                }
            }
        }
        if(!found)
        {
            arr.clear();
            from=0;
            to=0;
            highlight=0;
        }
        else if(found && !changed)
        {
            OnlySelectedRangeOfStringsRemain(lowerBound,from,to,highlight,arr,arr.size(),changed);
        }
        //--------------------------------------------------------------------------------------------------------------
    }
    else
    {
        string tmp="";
        for(int i=0;i<COLS-1;i++)
        {
            tmp+=' ';
        }
        mvprintw(4,0,tmp.c_str());
        attron(A_BOLD);
        mvprintw(4, 0, s.c_str());
        attroff(A_BOLD);
        // if user selected ingredient by pressing enter----------------------------------------------------------------
        if(s=="")
        {
            string selectedString=arr[highlight];
            arr.clear();
            int i=0;
            for(auto const &pair : myMap) {
                if(selectedString==pair.first)
                {
                    selected=i;
                }
                arr.push_back(pair.first);
                i++;
            }
            from=0;
            highlight=0;
            AssignValueToVariableTo(to,(int)arr.size());
            return;
        }
        //--------------------------------------------------------------------------------------------------------------
        //User pressed backspace
        typedef map<string, string>::const_iterator it_type;
        it_type lowerbound;
        for(it_type iterator = myMap.begin(); iterator != myMap.end(); ++iterator) {
            if(found)
            {
                if(iterator->first.length() < wordLenght)
                {
                    OnlySelectedRangeOfStringsRemain(lowerbound,from,to,highlight,arr,iterator,changed);
                    break;
                }
                bool b=true;
                for(unsigned int i=0;i<wordLenght;i++)
                {
                    if(s[i]!=iterator->first[i])
                    {
                        b=false;
                        break;
                    }
                }
                if(!b)
                {
                    OnlySelectedRangeOfStringsRemain(lowerbound,from,to,highlight,arr,iterator,changed);
                    break;
                }
            }
            else if(iterator->first.length() >= wordLenght)
            {
                bool b=true;
                for(unsigned int i=0;i<wordLenght;i++)
                {
                    if(s[i]!=iterator->first[i])
                    {
                        b=false;
                        break;
                    }
                }
                if(b)
                {
                    found = true;
                    lowerbound = iterator;
                }
            }
        }
        if(!found)
        {
            arr.clear();
            from=0;
            to=0;
            highlight=0;
        }
        else if(found && !changed)
        {
            OnlySelectedRangeOfStringsRemain(lowerbound,from,to,highlight,arr,myMap.end(),changed);
        }
        //--------------------------------------------------------------------------------------------------------------
    }
}

void Frontend::AssignValueToVariableTo(int &to, const int &sizeOfVector) {
    if(sizeOfVector>ingridientBoxHeight-3)
    {
        to=ingridientBoxHeight-3;
    }
    else
    {
        to=sizeOfVector;
    }
}

void Frontend::OnlySelectedRangeOfStringsRemain(unsigned int lowerbound, int &from, int &to, int &highlight, vector<string> &vectorOfStrings, unsigned int higherbound, bool &changed) {
    vector<string> tmp;
    for (unsigned int i = lowerbound; i != higherbound; ++i) {
        tmp.push_back(vectorOfStrings[i]);
    }
    vectorOfStrings.clear();
    vectorOfStrings=tmp;
    from=0;
    highlight=0;
    AssignValueToVariableTo(to,(int)vectorOfStrings.size());
    changed=true;
}

template<class T>
void Frontend::OnlySelectedRangeOfStringsRemain(T lowerbound, int &from, int &to, int &highlight, vector<string> &vectorOfStrings,T higherbound, bool &changed) {
    vector<string> tmp;
    for (T i = lowerbound; i != higherbound; ++i) {
        tmp.push_back(i->first);
    }
    vectorOfStrings.clear();
    vectorOfStrings=tmp;
    from=0;
    highlight=0;
    AssignValueToVariableTo(to,(int)vectorOfStrings.size());
    changed=true;
}


