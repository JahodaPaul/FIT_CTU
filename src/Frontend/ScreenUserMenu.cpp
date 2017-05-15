//
// Created by pjahoda on 5/7/17.
//

#include "ScreenUserMenu.h"

void ScreenUserMenu::Enter()
{
    userPressedEnter=true;
    switch(highlight)
    {
        case 0://SELECT SCREEN INGREDIENTS

            highlight=SCREEN_INGREDIENTS;
            break;
        case 1://SOMETHING

            highlight=-1;
            break;
        case 2://EXIT
            highlight=-2;
            break;
        default:
            return;
    }
}

void ScreenUserMenu::AssignData(Data &data)
{
    myData = &data;
}

void ScreenUserMenu::PrintStuff() const
{
    string printedString = "Username: ";
    printedString+=myData->GetUser()->GetUserName();
    mvprintw(secondWindowHeight, 1, printedString.c_str());
}

void ScreenUserMenu::SetVariables()
{
    secondWindowHeight=9;
    secondWindowWidth=22;
    secondWindowStartX=0;
    secondWindowStartY=0;
}

ScreenUserMenu::ScreenUserMenu()
{
    userPressedEnter = false;
    choices.clear();
    choices.push_back("FIND RECIPES");
    choices.push_back("SOMETHING");
    choices.push_back("EXIT");
    pictureVector.push_back("PROFILE");
    pictureVector.push_back("PICTURE");
    CountAverageStringSize(choices,averageStringSize);
    CountAverageStringSize(pictureVector,averageStringPicture);
    center=false;
}

ScreenUserMenu::~ScreenUserMenu()
{

}