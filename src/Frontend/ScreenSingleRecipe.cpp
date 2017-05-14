//
// Created by pjahoda on 5/12/17.
//

#include "ScreenSingleRecipe.h"

///main method of this class
int ScreenSingleRecipe::Run(const map <string, string> &mapa, vector <string> &pickedIngridients)
{
    //variables-----------------------------------------------------------------------------------------------------------------------------
    highlight=0;
    if(singleRecipe==NULL)
    {
        singleRecipe = myData->GetRecipeByIndex(pickedIngridients[0]);
    }
    SetVariables();
    WINDOW * menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
    WINDOW * secondWindow = newwin(secondWindowHeight,secondWindowWidth,secondWindowStartY,secondWindowStartX);
    //--------------------------------------------------------------------------------------------------------------------------------------

    clear();
    initscr();
    noecho();
    cbreak();

    //mvprintw(0, 0, singleRecipe->ToString(COLS).c_str());
    //mvprintw(1, 1, pickedIngridients[0].c_str());

    keypad(menu_win, TRUE);
    PrintStuff();
    refresh();
    PrintMenu(secondWindow,-1,pictureVector,true,secondWindowWidth,secondWindowHeight,averageStringPicture,0,(int)pictureVector.size());
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

            highlight=SCREEN_SINGLE_RECIPE;
            break;
        case 1://UNLIKE

            highlight=SCREEN_SINGLE_RECIPE;
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

void ScreenSingleRecipe::PrintStuff() const
{
    vector<string> ingredients = singleRecipe->GetIngredients();
    vector<int> ingredientWeights = singleRecipe->GetIngredientWeights();
    int numberOfIngredientsNotPrinted = 0;
    for(unsigned int i = 0; i< ingredients.size(); ++i)
    {
        if(ingredients[i]!="#")
        {
            string weight = to_string(ingredientWeights[i]);
            weight += " g";
            int posY = secondWindowHeight + i + 1 - numberOfIngredientsNotPrinted;
            mvprintw(posY, 1, weight.c_str());
            mvprintw(posY, 7, "|");
            mvprintw(posY, 8, ingredients[i].c_str());
        }
        else
        {
            numberOfIngredientsNotPrinted++;
        }
    }
}

void ScreenSingleRecipe::SetVariables()
{
    secondWindowHeight=9;
    secondWindowWidth=22;
    secondWindowStartX=0;
    secondWindowStartY=0;
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
    pictureVector.push_back("RECIPE");
    pictureVector.push_back("PICTURE");
    CountAverageStringSize(choices,averageStringSize);
    CountAverageStringSize(pictureVector,averageStringPicture);
    singleRecipe=NULL;
}

ScreenSingleRecipe::~ScreenSingleRecipe()
{

}