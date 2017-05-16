//
// Created by pjahoda on 4/21/17.
//

#ifndef RECIPE_MANAGER_DATA_H
#define RECIPE_MANAGER_DATA_H

#include "Connection.h"
#include <set>
#include "Recipe.h"
#include "User.h"

class Data : public Connection
{
public:
    Data();

    void GetDataFromDatabase(const int);

    void GetRecipesBySelectedIngredients(const vector <string> &selectedIngredients);

    map <string, string> &GetMapOfIngridients();

    map <string, string> &GetMapOfBeverages();

    map <string, string> &GetMapOfRecipes();

    string GetRecommendedRecipe(const Recipe &recipe, const int userID);

    ~Data();

    User *GetUser() const;

    vector<int> GetUsersThatLikedRecipe(const int &recipeID) const;

    void CreateNewUser(User *user1);

    void CreateRecipeBasedOnIngredientsSelected(const vector <string> &selectedIngredients);

    Recipe *GetRecipe() const;

    void DeleteRecipeBasedOnIngredients();

    void DeleteRecipesRetrievedFromDatabase();

    void UpdateScreenWidth(const int width);

    Recipe *GetRecipeByIndex(const string &index) const;

    void LikeRecipe(const int &userID, const Recipe *currentRecipe);

    void UnlikeRecipe(const int &userID, const Recipe *currentRecipe);

    void AddBeverageToMenuTable(const int &userId, const string &name);

    void DeleteBeverageFromMenuTable(const int &userId, const string &name);

    void AddRecipeToMenuTable(const int &userID, const int &toBeAddedRecipeID);

    void DeleteRecipeFromMenuTable(const int &userID, const int &toBeDeletedRecipeID);

    void GetDataFromMenuTable(const int &userID,vector<string> & menu);

    int HowManyRecipesUserLikes(const int &userID) const;

    void DeleteMapOfUsersAndRecipesTheyLiked();

    void SetRecommendedRecipe();

    static int idOfRecommendedRecipe;
protected:
private:
    void CopyIntoMap(const pqxx::result &, const string, map <string, string> &);

    void CopyIntoMapRecipes(const pqxx::result &, map<int, vector<Recipe *> > &);

    void FindItInAMapOfIngredients(string category, vector <string> &ingredients, const vector <string> &selectedIngredients);

    map <string, string> beveragesAndCategory;
    map <string, string> foodNameAndCategory;
    map<int, vector<Recipe *> > mapOfUsersAndRecipesTheyLiked;

    User *user;

    vector<Recipe *> recipesSelectByIngredients;
    map <string, string> recipesString;

    Recipe *recipe;
    Recipe *recommendedRecipe;

    int screenWidth;


};

#endif //RECIPE_MANAGER_DATA_H
