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
    map<string,string>& GetMapOfIngridients();
    Recipe& GetRecommendedRecipe(const Recipe& recipe, const int userID);
    ~Data();
    User * GetUser();
    void CreateNewUser(User * user1);
protected:
private:
    void CopyIntoMap(const pqxx::result &,const string,map<string,string> &);
    void CopyIntoMapRecipes(const pqxx::result &,map<int,vector<Recipe*> > &);
    map<string,string> beveragesAndCategory;
    map<string,string> foodNameAndCategory;
    map<int,vector<Recipe *> > mapOfUsersAndRecipesTheyLiked;
    User * user;

};

#endif //RECIPE_MANAGER_DATA_H
