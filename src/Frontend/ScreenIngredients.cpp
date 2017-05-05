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
int ScreenIngredients::Run(const map<string, string> & mapa) {
    //variables---------------------------------------------------------------------------------------------------------
    highlight=0;
    userPressedEnter=false;
    bool userPressedDoubleEnter=false,finishSelection=false;
    int from=0,to=0,picked=0,selected=0;
    string ingredientSelectionString="",temporaryString;
    int ingridientBoxHeight= LINES-5;
    int ingridientBoxWidth=COLS-30;
    int ingridientStartx = 0;
    int ingridientStarty = LINES-ingridientBoxHeight;
    int pickedIngridientsBoxHeight=ingridientBoxHeight;
    int pickedIngridientsBoxWidth=COLS-ingridientBoxWidth;
    int pickedIngridientsStartx=ingridientBoxWidth;
    int pickedIngridientsStarty=ingridientStarty;
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
        {	case KEY_UP://arrow up
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
            case KEY_DOWN://arrow down
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
                //user selected ingredient or is done selecting
                ingredientSelectionString="";
                PrintUserTypedIngredient(ingredientSelectionString,options,false,mapa,from,to,highlight,selected);
                menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                RefreshWholeWindow(menu_win);
                if(userPressedEnter)
                {
                    userPressedDoubleEnter=true;
                }
                else
                {
                    if(!Contain(pickedIngridients,options[selected])) {
                        picked++;
                        pickedIngridients.push_back(options[selected]);
                    }
                    PrintMenu(menuWinPickedIngridients,-1,pickedIngridients,false,pickedIngridientsBoxWidth,pickedIngridientsBoxHeight,0,0,picked);
                }
                userPressedEnter=!userPressedEnter;
                break;
            case KEY_BACKSPACE:
                //user deleted character
                temporaryString="";
                for(int i=0;i<(int)(ingredientSelectionString.length())-1;i++)
                {
                    temporaryString+=ingredientSelectionString[i];
                }
                ingredientSelectionString=temporaryString;
                PrintUserTypedIngredient(ingredientSelectionString,options,false,mapa,from,to,highlight,selected);
                menu_win = newwin(ingridientBoxHeight, ingridientBoxWidth, ingridientStarty, ingridientStartx);
                RefreshWholeWindow(menu_win);
                if(userPressedEnter)
                {
                    finishSelection=true;
                }
                userPressedEnter=false;
                break;
            default:
                //user pressed character other than backspace, enter and arrows up and down
                if(((key>96 && key < 123) || (key > 64 && key < 91) || (key > 47 && key < 58)) && (key!=KEY_RIGHT) && (key!=KEY_LEFT))
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
        return 1;
    }
    return 0;
    //return highlight;

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
