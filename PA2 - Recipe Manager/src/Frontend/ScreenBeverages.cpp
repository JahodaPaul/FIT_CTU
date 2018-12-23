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
            picked++;
            myPickedIngridients.push_back(options[selected]);
            myData->UpdateMenu(myData->recipesMenu,myPickedIngridients);
            myData->AddBeverageToMenuTable(myData->GetUser()->GetUserId(),options[selected]);
        }
        PrintMenu(menuWinPickedIngridients, -1, myPickedIngridients, false, secondWindowWidth, secondWindowHeight, 0, 0, picked);
    }
    userPressedEnter = !userPressedEnter;
}

void ScreenBeverages::AssignData(Data &data)
{
    myData = &data;
}

ScreenBeverages::ScreenBeverages()
{

}

ScreenBeverages::~ScreenBeverages()
{

}