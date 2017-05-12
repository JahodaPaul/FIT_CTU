//
// Created by pjahoda on 5/12/17.
//

#include "ScreenSingleRecipe.h"

///main method of this class
int ScreenSingleRecipe::Run(const map <string, string> &mapa, vector <string> &pickedIngridients)
{
    Recipe *recipe = myData->GetRecipeByIndex(pickedIngridients[0]);
    WINDOW * menu_win = newwin(5, 5, 5, 5);
    clear();
    initscr();
    noecho();
    cbreak();

    mvprintw(0, 0, recipe->ToString(COLS).c_str());
    mvprintw(1, 1, pickedIngridients[0].c_str());

    refresh();
    while(1)
    {
        key = wgetch(menu_win);
        ReactToUserInput(key);
        if(finishSelection)
        {
            break;
        }
    }

    clrtoeol();
    refresh();
    endwin();
    system("clear");

    return 0;
}

void ScreenSingleRecipe::Enter()
{
    //TODO
    finishSelection = true;
}

void ScreenSingleRecipe::AssignData(Data &data)
{
    myData = &data;
}


ScreenSingleRecipe::ScreenSingleRecipe()
{
    myData = NULL;
    finishSelection = false;
}

ScreenSingleRecipe::~ScreenSingleRecipe()
{

}