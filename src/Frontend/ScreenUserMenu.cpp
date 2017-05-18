//
// Created by pjahoda on 5/7/17.
//

#include "ScreenUserMenu.h"

void ScreenUserMenu::Enter()
{
    if(!thirdWindowSelected)
    {
        userPressedEnter = true;
        switch(highlight)
        {
            case 0://SELECT SCREEN INGREDIENTS

                highlight = SCREEN_INGREDIENTS;
                break;
            case 1://SELECT SCREEN BEVERAGES

                highlight = SCREEN_BEVERAGES;
                break;
            case 2://EXIT
                highlight = -2;
                break;
            default:
                return;
        }
    }
    else
    {
        // TODO delete beverage/recipe from menu table in database
    }
}

void ScreenUserMenu::KeyLeft()
{
    ChangeFocus();
}

void ScreenUserMenu::KeyRight()
{
    ChangeFocus();
}

void ScreenUserMenu::AssignData(Data &data)
{
    myData = &data;
}

void ScreenUserMenu::PrintStuff() const
{
    string printedString = "Username: ";
    printedString += myData->GetUser()->GetUserName();
    mvprintw(secondWindowHeight, 1, printedString.c_str());
    printedString = "Number of liked recipes: ";
    int tmp = myData->HowManyRecipesUserLikes(myData->GetUser()->GetUserId());
    printedString += to_string(tmp);
    mvprintw(secondWindowHeight+1, 1, printedString.c_str());
    mvprintw(secondWindowHeight+2, 1, "My menu: ");
}

void ScreenUserMenu::SetVariables()
{
    secondWindowHeight = 9;
    secondWindowWidth = 22;
    secondWindowStartX = 0;
    secondWindowStartY = 0;
    thirdWindowStartY=secondWindowHeight+3;
    thirdWindowStartX=0;
    thirdWindowWidth=COLS-24;
    thirdWindowHeight=LINES-thirdWindowStartY;
    vectorForThirdWindow=myData->menu;
}

ScreenUserMenu::ScreenUserMenu()
{
    userPressedEnter = false;
    choices.clear();
    choices.push_back("FIND RECIPES");
    choices.push_back("ADD BEVERAGES TO MENU");
    choices.push_back("EXIT");
    pictureVector.push_back("PROFILE");
    pictureVector.push_back("PICTURE");
    CountAverageStringSize(choices, averageStringSize);
    CountAverageStringSize(pictureVector, averageStringPicture);
    center = false;
}

ScreenUserMenu::~ScreenUserMenu()
{

}