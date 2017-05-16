//
// Created by pjahoda on 5/16/17.
//

#include "ScreenBeverages.h"

void ScreenBeverages::Enter()
{
    ingredientSelectionString = "";
    PrintUserTypedIngredient(ingredientSelectionString, options, false, *myMap, from, to, highlight, selected, firstWindowHeight);
    menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
    RefreshWholeWindow(menu_win);
    if(userPressedEnter)
    {
        finishSelection = true;
    }
    else
    {
        if(!Contain(myPickedIngridients, options[selected]))
        {
            ///TODO WRITE IT INTO DATABASE
            //myData->DeleteRecipesRetrievedFromDatabase();
            picked++;
            myPickedIngridients.push_back(options[selected]);
            //myData->GetRecipesBySelectedIngredients(myPickedIngridients);
        }
        PrintMenu(menuWinPickedIngridients, -1, myPickedIngridients, false, secondWindowWidth, secondWindowHeight, 0, 0, picked);
    }
    userPressedEnter = !userPressedEnter;
}

ScreenBeverages::ScreenBeverages()
{

}

ScreenBeverages::~ScreenBeverages()
{

}