//
// Created by pjahoda on 5/7/17.
//

#include "ScreenUserMenu.h"

void ScreenUserMenu::Enter()
{
    userPressedEnter=true;
    switch(highlight)
    {
        case 0://LIKE

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

void ScreenUserMenu::PrintStuff() const
{

}

ScreenUserMenu::ScreenUserMenu()
{
    userPressedEnter = false;
    choices.clear();
    choices.push_back("FIND RECIPES");
    choices.push_back("SOMETHING");
    choices.push_back("EXIT");
    CountAverageStringSize(choices,averageStringSize);
    center=false;
}

ScreenUserMenu::~ScreenUserMenu()
{

}