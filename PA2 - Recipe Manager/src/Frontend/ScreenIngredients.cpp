//
// Created by pjahoda on 5/3/17.
//

#include "ScreenIngredients.h"

/**
 * Shows list(vector) of strings and highlights selected one, user can select ingredient by pressing enter
 * scrolling using arrows is also fully functional
 * @param mapa
 * \return 0 if user pressed backspace and 1 if user is done selecting ingredients
 */
int ScreenIngredients::Run(const map <string, string> &mapa, vector <string> &pickedIngridients)
{
    //variables---------------------------------------------------------------------------------------------------------
    highlight = 0;
    userPressedEnter = false;
    userPressedDoubleEnter = false;
    finishSelection = false;
    from = 0;
    to = 0;
    picked = pickedIngridients.size();
    selected = 0;
    ingredientSelectionString = "";
    menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
    menuWinPickedIngridients = newwin(secondWindowHeight, secondWindowWidth, secondWindowStartY, secondWindowStartX);
    options.clear();
    this->myMap = &mapa;
    this->myPickedIngridients = pickedIngridients;
    picked = this->myPickedIngridients.size();
    //------------------------------------------------------------------------------------------------------------------

    clear();
    initscr();
    noecho();
    cbreak();

    for(auto const &pair : mapa)
    {
        options.push_back(pair.first);
    }

    PrintTextInfoForUser();
    SetVariables();
    keypad(menu_win, TRUE);
    refresh();
    AssignValueToVariableTo(to, (int) options.size(), firstWindowHeight);
    PrintMenu(menu_win, highlight, options, false, firstWindowWidth, firstWindowHeight, 0, from, to);
    if(selectedRecommendedRecipe)
    {
        PrintMenu(menuWinPickedIngridients, 0, myPickedIngridients, false, secondWindowWidth, secondWindowHeight, 0, 0,
                  (int) myPickedIngridients.size());
    }
    else
    {
        PrintMenu(menuWinPickedIngridients, -1, myPickedIngridients, false, secondWindowWidth, secondWindowHeight, 0, 0, picked);
    }



    while(1)
    {
        key = wgetch(menu_win);
        ReactToUserInput(key);
        PrintMenu(menu_win, highlight, options, false, firstWindowWidth, firstWindowHeight, 0, from, to);
        if(finishSelection)
        {
            break;
        }
    }


    pickedIngridients = this->myPickedIngridients;
    clrtoeol();
    refresh();
    endwin();
    system("clear");
    if(AreYouRecipeScreen())
    {
        return SCREEN_SINGLE_RECIPE;
    }
    if(userPressedDoubleEnter)
    {
        return SCREEN_RECIPES;
    }
    return SCREEN_USER_MENU;

}

void ScreenIngredients::KeyUp()
{
    if(!selectedRecommendedRecipe)
    {
        userPressedEnter = false;
        if(highlight == 0)
        {
            highlight = (int) (options.size() - 1);
            int diff = to - from;
            to = options.size();
            from = to - diff;
            menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
            RefreshWholeWindow(menu_win);
        }
        else
        {
            highlight--;
            if(from > highlight)
            {
                menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
                RefreshWholeWindow(menu_win);
                from--;
                to--;
            }
        }
    }
}

void ScreenIngredients::KeyDown()
{
    if(!selectedRecommendedRecipe)
    {
        userPressedEnter = false;
        if(highlight == (int) (options.size() - 1))
        {
            highlight = 0;
            int diff = to - from;
            from = 0;
            to = diff;
            menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
            RefreshWholeWindow(menu_win);
        }
        else
        {
            highlight++;
            if(highlight == to)
            {
                menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
                RefreshWholeWindow(menu_win);
                from++;
                to++;
            }
        }
    }
}

void ScreenIngredients::Enter()
{
    ingredientSelectionString = "";
    PrintUserTypedIngredient(ingredientSelectionString, options, false, *myMap, from, to, highlight, selected, firstWindowHeight);
    menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
    RefreshWholeWindow(menu_win);
    if(userPressedEnter)
    {
        userPressedDoubleEnter = true;
        finishSelection = true;
    }
    else
    {
        if(!Contain(myPickedIngridients, options[selected]))
        {
            myData->DeleteRecipesRetrievedFromDatabase();
            picked++;
            myPickedIngridients.push_back(options[selected]);
            myData->GetRecipesBySelectedIngredients(myPickedIngridients);
        }
        PrintMenu(menuWinPickedIngridients, -1, myPickedIngridients, false, secondWindowWidth, secondWindowHeight, 0, 0, picked);
    }
    userPressedEnter = !userPressedEnter;
}

void ScreenIngredients::Backspace()
{
    string temporaryString = "";
    for (int i = 0; i < (int) (ingredientSelectionString.length()) - 1; i++)
    {
        temporaryString += ingredientSelectionString[i];
    }
    ingredientSelectionString = temporaryString;
    if(myMap->size() != 0)
    {
        PrintUserTypedIngredient(ingredientSelectionString, options, false, *myMap, from, to, highlight, selected, firstWindowHeight);
    }
    menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
    RefreshWholeWindow(menu_win);
    if (userPressedEnter)
    {
        finishSelection = true;
    }
    userPressedEnter = false;
}

void ScreenIngredients::OtherKey()
{
    if((key > 96 && key < 123) || (key > 64 && key < 91) || (key > 47 && key < 58))
    {
        ingredientSelectionString += (char) key;

        if(myMap->size() != 0)
        {
            PrintUserTypedIngredient(ingredientSelectionString, options, true, *myMap, from, to, highlight, selected, firstWindowHeight);
        }
        menu_win = newwin(firstWindowHeight, firstWindowWidth, firstWindowStartY, firstWindowStartX);
        RefreshWholeWindow(menu_win);
        userPressedEnter = false;
        refresh();
    }
}

///refreshed curses WINDOW so it does not show visual bugs
void ScreenIngredients::RefreshWholeWindow(WINDOW *menu_win)
{
    keypad(menu_win, TRUE);
    PrintTextInfoForUser();
    refresh();
}

void ScreenIngredients::PrintTextInfoForUser() const
{
    mvprintw(0, 0, "To change selection use arrows or typing. Press enter to select a choice");
    mvprintw(1, 0, "Press enter and backspace to go back to menu.");
    mvprintw(2, 0, "Press double enter to search for recipes.");
    string s = "";
    for(int i = 0; i < COLS; i++)
    {
        s += '-';
    }
    mvprintw(3, 0, s.c_str());
    mvprintw(4, COLS - 30, "|");
    attron(A_BOLD);
    mvprintw(4, COLS - 29, "   Selected ingredients");
    attroff(A_BOLD);
}

ScreenIngredients::ScreenIngredients()
{
    firstWindowHeight = LINES - 5;
    firstWindowWidth = COLS - 30;
    firstWindowStartX = 0;
    firstWindowStartY = LINES - firstWindowHeight;
    secondWindowHeight = firstWindowHeight;
    secondWindowWidth = COLS - firstWindowWidth;
    secondWindowStartX = firstWindowWidth;
    secondWindowStartY = firstWindowStartY;
    selectedRecommendedRecipe = false;
}

ScreenIngredients::~ScreenIngredients()
{

}
