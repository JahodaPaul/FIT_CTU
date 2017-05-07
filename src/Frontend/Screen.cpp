//
// Created by pjahoda on 5/3/17.
//

#include "Screen.h"

/**
 *
 * @param menu_win
 * @param highlight
 * @param choices
 * @param center
 * @param boxWidth
 * @param boxHeight
 * @param averageStringSize
 * @param from
 * @param to
 * It prints given a vector of strings in the middle or at the top left corner.
 * Can also highlight one of the strings given integer parameter highlight
 */
void Screen::PrintMenu(WINDOW *menu_win, const int highlight,const vector<string>& choices,const bool center,const int& boxWidth,const int& boxHeight,const int &averageStringSize,const int& from,const int& to)
{
    int x,y;
    if(center)
    {
        x=(boxWidth/2 - averageStringSize/2);
        y=(boxHeight/2 - (to/2));
        if(to==1)
        {
            y=1;
        }
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

/**
 * @param login
 * @param password
 * gets username nad password
 */
void Screen::GetUserInfo(string &login, string &password) {
    GetUserInputOneLine("login: ",login,false);
    GetUserInputOneLine("password: ",password,true);
}

/**
 * Shows box in the middle of the screen where user types input
 * \param toBeShown string which is placed before user typed input
 * @param get
 * @param getPassword
 */
void Screen::GetUserInputOneLine(string toBeShown,string &get,const bool getPassword)
{
    //variables---------------------------------------------------------------------------------------------------------
    string temporaryString="";
    highlight=10;
    vector<string> shownToUser;
    shownToUser.push_back(toBeShown);
    userPressedEnter=false;
    clear();
    initscr();
    noecho();
    cbreak();
    int width=25;
    int height=3;
    Frontend::middleStartX = (COLS - width) / 2;
    Frontend::middleStartY = (LINES - height) / 3;
    WINDOW *menu_win = newwin(height, width, middleStartY, middleStartX);
    //------------------------------------------------------------------------------------------------------------------

    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Press enter to confirm input.");
    refresh();
    PrintMenu(menu_win,highlight, shownToUser,true,width,height,20,0,(int)shownToUser.size());
    while(1)
    {
        key = wgetch(menu_win);
        switch(key)
        {
            case KEY_BACKSPACE:
                //user deleted character
                temporaryString="";
                for(int i=0;i<(int)(get.length())-1;i++)
                {
                    temporaryString+=get[i];
                }
                get=temporaryString;
                if(getPassword)
                {
                    temporaryString="";
                    for(int i=0;i<(int)(get.length())-1;i++)
                    {
                        temporaryString+='*';
                    }
                }
                shownToUser[0]=toBeShown+temporaryString;
                menu_win = newwin(height, width, middleStartY, middleStartX);
                keypad(menu_win, TRUE);
                refresh();
                break;
            case 10:
                userPressedEnter=true;
                break;
            default:
                if((key>96 && key < 123) || (key > 64 && key < 91) || (key > 47 && key < 58))
                {
                    shownToUser[0]+=char(key);
                    get+=char(key);
                    if(getPassword)
                    {
                        temporaryString="";
                        for(int i=0;i<(int)(get.length())-1;i++)
                        {
                            temporaryString+='*';
                        }
                        shownToUser[0]=toBeShown+temporaryString;
                        shownToUser[0]+=(char)(key);
                    }
                    refresh();
                }
                break;
        }
        PrintMenu(menu_win,highlight, shownToUser,true,width,height,20,0,(int)shownToUser.size());
        if(userPressedEnter)
            break;
    }
    clrtoeol();
    refresh();
    endwin();
}

Screen::Screen() {
    userPressedEnter=false;
    highlight=0;
    key=0;
}

/**
 *
 * @param s
 * @param arr
 * @param newChar
 * @param myMap
 * @param from
 * @param to
 * @param highlight
 * @param selected
 * Shows list of strings based on user input
 * for example: users types character A, so only strings that begin with character A remain in vector of strings arr
 * it also reacts to character deletion using backspace and string selection using enter
 */
void Screen::PrintUserTypedIngredient(string &s,vector<string>& arr,bool newChar,const map<string,string>& myMap,int &from, int &to,int &highlight,int &selected) {
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

/// used by PrintUserTypedIngredient function so only range of strings remain in vector of strings
void Screen::OnlySelectedRangeOfStringsRemain(const unsigned int lowerbound, int &from, int &to, int &highlight, vector<string> &vectorOfStrings, const unsigned int higherbound, bool &changed) {
    vector<string> tmp;
    for (unsigned int i = lowerbound; i != higherbound; ++i)
    {
        tmp.push_back(vectorOfStrings[i]);
    }
    vectorOfStrings.clear();
    vectorOfStrings=tmp;
    from=0;
    highlight=0;
    AssignValueToVariableTo(to,(int)vectorOfStrings.size());
    changed=true;
}

/// used by PrintUserTypedIngredient function so only range of strings remain in vector of strings
template<class T>
void Screen::OnlySelectedRangeOfStringsRemain(const T lowerbound, int &from, int &to, int &highlight, vector<string> &vectorOfStrings,const T higherbound, bool &changed) {
    vector<string> tmp;
    for (T i = lowerbound; i != higherbound; ++i)
    {
        tmp.push_back(i->first);
    }
    vectorOfStrings.clear();
    vectorOfStrings=tmp;
    from=0;
    highlight=0;
    AssignValueToVariableTo(to,(int)vectorOfStrings.size());
    changed=true;
}