//
// Created by pjahoda on 5/7/17.
//

#include "ScreenRecipes.h"

void ScreenRecipes::Enter() {
    //TODO
    finishSelection=true;
}

void ScreenRecipes::PrintTextInfoForUser() const {
    mvprintw(0, 0, "Use arrow keys to go up and down. Press enter to select a recipe");
    mvprintw(1,0,"Use arrows left and right to move focus between screens");
    string s="";
    for(int i=0;i<COLS;i++)
    {
        s+='-';
    }
    mvprintw(2,0,s.c_str());

    attron(A_BOLD);
    mvprintw(pickedIngridientsStarty-1,1,"You might like this recipe: ");
    attroff(A_BOLD);
}

ScreenRecipes::ScreenRecipes() {
    ingridientBoxHeight= LINES-9;
    ingridientBoxWidth=COLS;
    ingridientStartx = 0;
    ingridientStarty = LINES-ingridientBoxHeight-6;
    pickedIngridientsBoxHeight=3;
    pickedIngridientsBoxWidth=ingridientBoxWidth;
    pickedIngridientsStartx=0;
    pickedIngridientsStarty=ingridientStarty+ingridientBoxHeight+2;
}

ScreenRecipes::~ScreenRecipes() {

}

