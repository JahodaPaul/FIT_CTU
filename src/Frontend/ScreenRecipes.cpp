//
// Created by pjahoda on 5/7/17.
//

#include "ScreenRecipes.h"

ScreenRecipes::ScreenRecipes() {
    ingridientBoxHeight= LINES-10;
    ingridientBoxWidth=COLS-1;
    ingridientStartx = 0;
    ingridientStarty = LINES-ingridientBoxHeight-5;
    pickedIngridientsBoxHeight=4;
    pickedIngridientsBoxWidth=ingridientBoxWidth;
    pickedIngridientsStartx=0;
    pickedIngridientsStarty=ingridientStarty+ingridientBoxHeight;
}

ScreenRecipes::~ScreenRecipes() {

}

void ScreenRecipes::Enter() {
    //TODO
    finishSelection=true;
}