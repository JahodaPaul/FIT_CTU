//
// Created by pjahoda on 5/7/17.
//

#include "ScreenUserMenu.h"

void ScreenUserMenu::Enter()
{
    userPressedEnter=true;
    if(!thirdWindowSelected)
    {
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
        if(highlightThirdWindow>=(int)myData->recipesMenu.size())
        {
            myData->DeleteBeverageFromMenuTable(myData->GetUser()->GetUserId(),vectorForThirdWindow[highlightThirdWindow]);
            myData->beveragesMenu.erase(myData->beveragesMenu.begin()+highlightThirdWindow-myData->recipesMenu.size());
        }
        else
        {
            myData->DeleteRecipeFromMenuTable(myData->GetUser()->GetUserId(),myData->GetRecipeIDBasedOnPositionInMenu(highlightThirdWindow));
            myData->recipesMenu.erase(myData->recipesMenu.begin()+highlightThirdWindow);
        }
        myData->UpdateMenu(myData->recipesMenu,myData->beveragesMenu);
        highlightThirdWindow=0;
        vectorForThirdWindow.erase(vectorForThirdWindow.begin()+highlightThirdWindow);
        highlight=SCREEN_USER_MENU;
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
    attron(A_BOLD);
    mvprintw(secondWindowHeight+1, 1, printedString.c_str());
    attroff(A_BOLD);
    mvprintw(secondWindowHeight+2, 1, "To remove selected recipe/beverage from menu, press enter.");
    mvprintw(secondWindowHeight+3, 1, "User arrows and enter.");
    attron(A_BOLD);
    mvprintw(secondWindowHeight+4, 1, "My menu: ");
    attroff(A_BOLD);
}

void ScreenUserMenu::SetVariables()
{
    secondWindowHeight = 9;
    secondWindowWidth = 22;
    secondWindowStartX = 0;
    secondWindowStartY = 0;
    thirdWindowStartY=secondWindowHeight+5;
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