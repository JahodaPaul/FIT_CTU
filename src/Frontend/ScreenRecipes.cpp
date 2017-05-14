//
// Created by pjahoda on 5/7/17.
//

#include "ScreenRecipes.h"

void ScreenRecipes::Enter()
{
    //TODO
    if(!selectedRecommendedRecipe)
    {
        string unusedString = "";
        PrintUserTypedIngredient(unusedString, options, false, *myMap, from, to, highlight, selected, firstWindowHeight);
        auto it = myMap->find(options[selected]);
        myPickedIngridients.clear();
        myPickedIngridients.push_back(it->second);
    }
    else if(selectedRecommendedRecipe)
    {
        myPickedIngridients.clear();
        myPickedIngridients.push_back("-1");
    }
    finishSelection = true;
}

/**
 * Changes focus from list of recipes retrieved from database based on selected recipes
 * to recommended recipe and visa versa when arrow key left or right is pressed
 */
void ScreenRecipes::ChangeFocus()
{
    if(options.size() != 0)
    {
        selectedRecommendedRecipe = !selectedRecommendedRecipe;
    }
    if(!selectedRecommendedRecipe)
    {
        highlight = (int) (options.size() - 1);
        KeyDown();
        PrintMenu(menuWinPickedIngridients, -1, myPickedIngridients, false, secondWindowWidth, secondWindowHeight, 0, 0,
                  (int) myPickedIngridients.size());
    }
    else
    {
        highlight = -1;
        PrintMenu(menuWinPickedIngridients, 0, myPickedIngridients, false, secondWindowWidth, secondWindowHeight, 0, 0,
                  (int) myPickedIngridients.size());
    }
}

void ScreenRecipes::KeyLeft()
{
    ChangeFocus();
}

void ScreenRecipes::KeyRight()
{
    ChangeFocus();
}

void ScreenRecipes::PrintTextInfoForUser() const
{
    mvprintw(0, 0, "Arrows top and down to scroll, left and right to switch focus between screens.");
    mvprintw(1, 0, "Type to activate smart selection.");
    mvprintw(2, 0, "To select recipe press enter.");
    string s = "";
    for(int i = 0; i < COLS; i++)
    {
        s += '-';
    }
    mvprintw(3, 0, s.c_str());

    attron(A_BOLD);
    mvprintw(secondWindowStartY - 1, 1, "You might like this recipe: ");
    attroff(A_BOLD);
}

void ScreenRecipes::SetVariables()
{
    if(options.size() == 0)
    {
        selectedRecommendedRecipe = true;
    }
}

ScreenRecipes::ScreenRecipes()
{
    firstWindowHeight = LINES - 10;
    firstWindowWidth = COLS;
    firstWindowStartX = 0;
    firstWindowStartY = LINES - firstWindowHeight - 5;
    secondWindowHeight = 3;
    secondWindowWidth = firstWindowWidth;
    secondWindowStartX = 0;
    secondWindowStartY = firstWindowStartY + firstWindowHeight + 2;
    selectedRecommendedRecipe = false;
}

ScreenRecipes::~ScreenRecipes()
{

}

