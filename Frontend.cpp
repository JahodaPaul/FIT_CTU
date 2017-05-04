//
// Created by pjahoda on 4/21/17.
//
#include "Frontend.h"
#include "Screen.h"
#include "ScreenLogin.h"
#include "ScreenIngredients.h"


void Frontend::Run(Connection &c,Data & data) {
    //variables---------------------------------------------------------------------------------------------------------
    Screen * loginScreen = new ScreenLogin();
    Screen * ingredientScreen = new ScreenIngredients();
    bool loggedIn=false,downloadedData=false;
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
    downloadedData=true;
    ingredientScreen->Run(data.GetMapOfIngridients());


    // at the end of program delete Screen instances
    delete loginScreen;
    delete ingredientScreen;
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
    if(sizeOfVector>(LINES-5)-3)//TODO do not hardcode it
    {
        to=(LINES-5)-3;
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
