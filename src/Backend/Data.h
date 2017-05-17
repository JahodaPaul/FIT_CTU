//
// Created by pjahoda on 4/21/17.
//

#ifndef RECIPE_MANAGER_DATA_H
#define RECIPE_MANAGER_DATA_H

//#include "Connection.h"
#include "DataSQL.h"


class Data : public DataSQL
{
public:
    Data();

    ~Data();

    map <string, string> &GetMapOfIngridients();

    map <string, string> &GetMapOfBeverages();

    map <string, string> &GetMapOfRecipes();

    string GetRecommendedRecipe(const Recipe &recipe, const int userID);

    User *GetUser() const;

    vector<int> GetUsersThatLikedRecipe(const int &recipeID) const;

    void CreateNewUser(User *user1);

    void CreateRecipeBasedOnIngredientsSelected(const vector <string> &selectedIngredients);

    Recipe *GetRecipe() const;

    void DeleteRecipeBasedOnIngredients();

    void DeleteRecipesRetrievedFromDatabase();

    void UpdateScreenWidth(const int width);

    void UpdateMenu(const vector<string> & recipes, const vector<string> &beverages);

    Recipe *GetRecipeByIndex(const string &index) const;

    int HowManyRecipesUserLikes(const int &userID) const;

    void DeleteMapOfUsersAndRecipesTheyLiked();

    void SetRecommendedRecipe();

    static int idOfRecommendedRecipe;
protected:
private:
    void FindItInAMapOfIngredients(string category, vector <string> &ingredients, const vector <string> &selectedIngredients);
};

#endif //RECIPE_MANAGER_DATA_H
