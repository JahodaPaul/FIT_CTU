//
// Created by pjahoda on 5/3/17.
//

#include "ScreenIngredients.h"

/**
 * Shows list(vector) of strings and highlights selected one, user can select ingredient by pressing enter
 * scrolling using arrows is also fully functional
 * @param mapa
 * \return 0 if user pressed backspace and 1 if user is done selecting ingredients
 */
int ScreenIngredients::Run(const map<string, string> & mapa,vector<string> & pickedIngridients) {
    //variables---------------------------------------------------------------------------------------------------------
    highlight=0;
    userPressedEnter=false;
    userPressedDoubleEnter=false;finishSelection=false;
    from=0;to=0;picked=0;selected=0;
    ingredientSelectionString="";
    //string temporaryString;
    ingridientBoxHeight= LINES-5;
    ingridientBoxWidth=COLS-30;
    ingridientStartx = 0;
    ingridientStarty = LINES-ingridientBoxHeight;
    pickedIngridientsBoxHeight=ingridientBoxHeight;
    pickedIngridientsBoxWidth=COLS-ingridientBoxWidth;
    pickedIngridientsStartx=ingridientBoxWidth;
    pickedIngridientsStarty=ingridientStarty;
    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
    menuWinPickedIngridients = newwin(pickedIngridientsBoxHeight,pickedIngridientsBoxWidth,pickedIngridientsStarty,pickedIngridientsStartx);
    options.clear();
    this->myMap=&mapa;
    this->myPickedIngridients=pickedIngridients;
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
    PrintMenu(menuWinPickedIngridients,-1,myPickedIngridients,false,pickedIngridientsBoxWidth,pickedIngridientsBoxHeight,0,0,picked);


    while(1)
    {
        key = wgetch(menu_win);
        ReactToUserInput(key);
        PrintMenu(menu_win, highlight,options,false,ingridientBoxWidth,ingridientBoxHeight,0,from,to);
        if(finishSelection)
            break;
    }


    pickedIngridients=this->myPickedIngridients;
    clrtoeol();
    refresh();
    endwin();
    system("clear");
    if(userPressedDoubleEnter)
    {
        //TODO
        return 1;
    }
    return 0;
    //return highlight;

}

void ScreenIngredients::KeyUp() {
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
}

void ScreenIngredients::KeyDown() {
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
}

void ScreenIngredients::Enter() {
    ingredientSelectionString="";
    PrintUserTypedIngredient(ingredientSelectionString,options,false,*myMap,from,to,highlight,selected);
    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
    RefreshWholeWindow(menu_win);
    if(userPressedEnter)
    {
        userPressedDoubleEnter=true;
    }
    else
    {
        if(!Contain(myPickedIngridients,options[selected])) {
            picked++;
            myPickedIngridients.push_back(options[selected]);
        }
        PrintMenu(menuWinPickedIngridients,-1,myPickedIngridients,false,pickedIngridientsBoxWidth,pickedIngridientsBoxHeight,0,0,picked);
    }
    userPressedEnter=!userPressedEnter;
}

void ScreenIngredients::Backspace() {
    string temporaryString="";
    for(int i=0;i<(int)(ingredientSelectionString.length())-1;i++)
    {
        temporaryString+=ingredientSelectionString[i];
    }
    ingredientSelectionString=temporaryString;
    PrintUserTypedIngredient(ingredientSelectionString,options,false,*myMap,from,to,highlight,selected);
    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
    RefreshWholeWindow(menu_win);
    if(userPressedEnter)
    {
        finishSelection=true;
    }
    userPressedEnter=false;
}

void ScreenIngredients::OtherKey() {
    if((key>96 && key < 123) || (key > 64 && key < 91) || (key > 47 && key < 58))
        ingredientSelectionString+=(char)key;
    PrintUserTypedIngredient(ingredientSelectionString,options,true,*myMap,from,to,highlight,selected);
    menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
    RefreshWholeWindow(menu_win);
    userPressedEnter=false;
    refresh();
}

///refreshed curses WINDOW so it does not show visual bugs
void ScreenIngredients::RefreshWholeWindow(WINDOW *menu_win) {
    keypad(menu_win, TRUE);
    PrintTextInfoForUser();
    refresh();
}

void ScreenIngredients::PrintTextInfoForUser() const {
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    mvprintw(1,0,"Press double enter to Search for recipes containing chosen ingredients.");
    mvprintw(2,0,"Press enter and backspace to exit the application.");
    string s="";
    for(int i=0;i<COLS;i++)
    {
        s+='-';
    }
    mvprintw(3,0,s.c_str());
    mvprintw(4,COLS-30,"|");
    attron(A_BOLD);
    mvprintw(4,COLS-29,"   Selected ingredients");
    attroff(A_BOLD);
}

ScreenIngredients::ScreenIngredients() {

}

ScreenIngredients::~ScreenIngredients() {

}
