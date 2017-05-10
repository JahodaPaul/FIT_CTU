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
    mvprintw(secondWindowStartY-1,1,"You might like this recipe: ");
    attroff(A_BOLD);
}

ScreenRecipes::ScreenRecipes() {
    firstWindowHeight= LINES-9;
    firstWindowWidth=COLS;
    firstWindowStartX = 0;
    firstWindowStartY = LINES-firstWindowHeight-6;
    secondWindowHeight=3;
    secondWindowWidth=firstWindowWidth;
    secondWindowStartX=0;
    secondWindowStartY=firstWindowStartY+firstWindowHeight+2;
}

ScreenRecipes::~ScreenRecipes() {

}

