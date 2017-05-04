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

void Screen::OnlySelectedRangeOfStringsRemain(unsigned int lowerbound, int &from, int &to, int &highlight, vector<string> &vectorOfStrings, unsigned int higherbound, bool &changed) {
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
void Screen::OnlySelectedRangeOfStringsRemain(T lowerbound, int &from, int &to, int &highlight, vector<string> &vectorOfStrings,T higherbound, bool &changed) {
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