//
// Created by pjahoda on 5/12/17.
//

#include "ScreenSingleRecipe.h"

///main method of this class
int ScreenSingleRecipe::Run(const map <string, string> &mapa, vector <string> &pickedIngridients)
{
    highlight=0;
    Recipe *recipe = myData->GetRecipeByIndex(pickedIngridients[0]);
    WINDOW * menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
    clear();
    initscr();
    noecho();
    cbreak();

    mvprintw(0, 0, recipe->ToString(COLS).c_str());
    mvprintw(1, 1, pickedIngridients[0].c_str());

    keypad(menu_win, TRUE);
    refresh();
    PrintMenu(menu_win, highlight, choices, false, firstWindowWidth, firstWindowHeight, averageStringSize, 0, (int) choices.size());
    while(1)
    {
        key = wgetch(menu_win);
        ReactToUserInput(key);
        PrintMenu(menu_win, highlight, choices, false, firstWindowWidth, firstWindowHeight, averageStringSize, 0, (int) choices.size());
        if(finishSelection)
        {
            break;
        }
    }

    clrtoeol();
    refresh();
    endwin();
    system("clear");

    return highlight;
}

void ScreenSingleRecipe::Enter()
{
    finishSelection = true;
    switch(highlight)
    {
        case 0://LIKE

            highlight=-1;
            break;
        case 1://UNLIKE

            highlight=-1;
            break;
        case 2:
            highlight=SCREEN_RECIPES;
            break;
        case 3:
            highlight=SCREEN_INGREDIENTS;
            break;
        case 4:
            highlight=SCREEN_USER_MENU;
            break;
        default:
            return;
    }
}

void ScreenSingleRecipe::AssignData(Data &data)
{
    myData = &data;
}


ScreenSingleRecipe::ScreenSingleRecipe()
{
    myData = NULL;
    finishSelection = false;
    choices.clear();
    choices.push_back("LIKE");
    choices.push_back("UNLIKE");
    choices.push_back("Recipe selection");
    choices.push_back("Ingredients selection");
    choices.push_back("Main menu");
    CountAverageStringSize(choices,averageStringSize);
}

ScreenSingleRecipe::~ScreenSingleRecipe()
{

}