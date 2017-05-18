//
// Created by Pavel on 5/17/2017.
//

#ifndef RECIPE_MANAGER_DATASQL_H
#define RECIPE_MANAGER_DATASQL_H

#include "Connection.h"
#include <set>
#include "Recipe.h"
#include "User.h"

class DataSQL:public Connection
{
public:
    DataSQL();

    ~DataSQL();

    void GetDataFromDatabase(const int);

    void GetRecipesBySelectedIngredients(const vector <string> &selectedIngredients);

    void LikeRecipe(const int &userID, const Recipe *currentRecipe);

    void UnlikeRecipe(const int &userID, const Recipe *currentRecipe);

    void AddBeverageToMenuTable(const int &userId, const string &name);

    void DeleteBeverageFromMenuTable(const int &userId, const string &name);

    void AddRecipeToMenuTable(const int &userID, Recipe * toBeAddedRecipe);

    void DeleteRecipeFromMenuTable(const int &userID, const int &toBeDeletedRecipeID);

    void GetDataFromMenuTable(const result &R,vector<string> & menu, vector<string> &recipesMenu, vector<string> &beveragesMenu);

    vector <string> beveragesMenu;
    vector <string> recipesMenu;
    vector <string> menu;

protected:
    map <string, string> beveragesAndCategory;
    map <string, string> foodNameAndCategory;
    map<int, vector<Recipe *> > mapOfUsersAndRecipesTheyLiked;
    map<int ,vector<Recipe *> > mapOfRecipesInMenu;

    User *user;

    vector<Recipe *> recipesSelectByIngredients;
    map <string, string> recipesString;



    Recipe *recipe;
    Recipe *recommendedRecipe;

    int screenWidth;
private:
    void CopyIntoMap(const pqxx::result &, const string, map <string, string> &);

    void CopyIntoMapRecipes(const pqxx::result &, map<int, vector<Recipe *> > &);
};

#endif //RECIPE_MANAGER_DATASQL_H
