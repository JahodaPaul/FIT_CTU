//
// Created by pjahoda on 4/21/17.
//

#include "Data.h"
#include <iostream>

///same purpose as SetRecommendedRecipe function, when user presses LIKE/UNLIKE its value is nonzero, else it is zero
int Data::idOfRecommendedRecipe = 0;

/**
 * \return map foodNameAndCategory
 */
map <string, string> &Data::GetMapOfIngridients()
{
    return foodNameAndCategory;
}

/// \return map beveragesAndCategory
map <string, string> &Data::GetMapOfBeverages()
{
    return beveragesAndCategory;
}

/**
 * \return map recipesString
 */
map <string, string> &Data::GetMapOfRecipes()
{
    return recipesString;
}


/**
 * finds another user that likes same types of recipes based on average number of ingredients that are the same in
 * the list of user liked recipes and then finds the recipe from the list which most corresponds to the
 * Recipe(selected ingredients) that logged in user is looking for.
 * @param recipe
 * \param userID
 * \return recommended Recipe object
 */
string Data::GetRecommendedRecipe(const Recipe &recipe, const int userID)
{
    int max = 0;
    typedef map<int, vector < Recipe * > >::iterator it_type;
    it_type it;
    it_type userIt = mapOfUsersAndRecipesTheyLiked.end();
    for(it_type iterator = mapOfUsersAndRecipesTheyLiked.begin(); iterator != mapOfUsersAndRecipesTheyLiked.end(); ++iterator)
    {
        if((*iterator).first == userID)
        {
            userIt = iterator;
            continue;
        }
        int sum = 0, average = 0;
        for(unsigned int j = 0; j < (*iterator).second.size(); j++)
        {
            sum += (*iterator).second[j]->HowMuchAreRecipesSame(recipe);
        }
        average = sum / ((int) (*iterator).second.size() + 1);
        if(average > max)
        {
            max = average;
            it = iterator;
        }
    };

    max = 0;
    Recipe *p = NULL;
    bool didNotFoundRecipeThatYouDoNotAlreadyLike = false;

    for(unsigned int j = 0; j < (*it).second.size(); j++)
    {
        if((*it).second[j]->HowMuchAreRecipesSame(recipe) > max)
        {
            if(userIt == mapOfUsersAndRecipesTheyLiked.end())
            {
                max = (*it).second[j]->HowMuchAreRecipesSame(recipe);
                p = (*it).second[j];
            }
            else
            {
                bool tmp = false;
                for(unsigned int k = 0; k < (*userIt).second.size(); k++)
                {
                    if((*it).second[j]->GetRecipeId() == (*userIt).second[k]->GetRecipeId())
                    {
                        tmp = true;
                        break;
                    }
                }
                if(!tmp || didNotFoundRecipeThatYouDoNotAlreadyLike)
                {
                    max = (*it).second[j]->HowMuchAreRecipesSame(recipe);
                    p = (*it).second[j];
                }
            }
        }
        if(j + 1 == (*it).second.size())
        {
            if(p == NULL)
            {
                didNotFoundRecipeThatYouDoNotAlreadyLike = true;
                j = -1;
            }
        }
    }
    this->recommendedRecipe = p;
    return (*p).ToString(this->screenWidth);
}

/// deletes objects created by method GetRecipesBySelectedIngredients
void Data::DeleteRecipesRetrievedFromDatabase()
{
    recipesString.clear();
    for(unsigned int i = 0; i < recipesSelectByIngredients.size(); ++i)
    {
        delete recipesSelectByIngredients[i];
    }
    recipesSelectByIngredients.clear();
}

void Data::CreateRecipeBasedOnIngredientsSelected(const vector <string> &selectedIngredients)
{
    if(recipe == NULL)
    {
        vector <string> ingredients;
        vector<int> weight;
        for(unsigned i = 0; i < 9; i++)
        {
            weight.push_back(0);
        }
        FindItInAMapOfIngredients("meat", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("side", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("cheese", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("fruit", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("vegetable", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("spice", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("spice2", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("nuts", ingredients, selectedIngredients);
        FindItInAMapOfIngredients("vegetable2", ingredients, selectedIngredients);
        recipe = new Recipe(ingredients, weight, -1);
    }
}

///helper method for method CreateRecipeBasedOnIngredientsSelected
void Data::FindItInAMapOfIngredients(string category, vector <string> &ingredients, const vector <string> &selectedIngredients)
{
    if(category == "spice")
    {
        ingredients.push_back("salt");
        return;
    }
    for(const string &ingredient : selectedIngredients)
    {
        auto it = foodNameAndCategory.find(ingredient);
        if(it->second == category)
        {
            ingredients.push_back(ingredient);
            return;
        }
    }
    // should not be # as it would mean user does not want meat for example,
    // but user just might want something more than meat
    ingredients.push_back(".");
}

/// \return pointer to recipe created by selected ingredients (used to find recommended recipe)
Recipe *Data::GetRecipe() const
{
    return this->recipe;
}

/**
 * \param index string index of selected recipe
 * \return pointer to selected(given by index parameter) Recipe object
 */
Recipe *Data::GetRecipeByIndex(const string &index) const
{
    int indexInt = stoi(index);
    //if user selected recommended recipe
    if(indexInt == -1)
    {
        return this->recommendedRecipe;
    }
    else
    {
        return this->recipesSelectByIngredients[indexInt];
    }
}

/// deletes recipe created based on user selected ingredients
void Data::DeleteRecipeBasedOnIngredients()
{
    if(this->recipe != NULL)
    {
        delete recipe;
    }
    recipe = NULL;
}

/// \return pointer to a user
User *Data::GetUser() const
{
    return this->user;
}

/// creates a user if it does not exist
void Data::CreateNewUser(User *user1)
{
    if(this->user == NULL)
    {
        this->user = user1;
    }
}

void Data::UpdateScreenWidth(const int width)
{
    screenWidth = width;
}

///serches map mapOfUsersAndRecipesTheyLiked for users that liked the same recipe(with same id) as recipeID in the parameter
vector<int> Data::GetUsersThatLikedRecipe(const int &recipeID) const
{
    vector<int> usersID;
    for(auto const &ent1 : mapOfUsersAndRecipesTheyLiked)
    {
        for(auto const &ent2 : ent1.second)
        {
            if(ent2->GetRecipeId() == recipeID)
            {
                usersID.push_back(ent1.first);
            }
        }
    }
    return usersID;
}

int Data::HowManyRecipesUserLikes(const int &userID) const
{
    int result = 0;
    for(auto const &ent1 : mapOfUsersAndRecipesTheyLiked)
    {
        if(ent1.first == userID)
        {
            result = (int) ent1.second.size();
            return result;
        }
    }
    return result;
}

///frees Recipe * and clears map
void Data::DeleteMap(map<int, vector<Recipe *> > &myMap)
{
    for(auto &ent1 : myMap)
    {
        for(auto &ent2 : ent1.second)
        {
            delete ent2;
        }
        ent1.second.clear();
    }
    mapOfUsersAndRecipesTheyLiked.clear();
}

/// calls DeleteMap function with mapOfUsersAndRecipesTheyLiked parameter
void Data::DeleteMapOfUsersAndRecipesTheyLiked()
{
    DeleteMap(mapOfUsersAndRecipesTheyLiked);
}

/// this function has only one purpose, when a user is a in a screen ScreenSingleRecipe  and presses LIKE/UNLIKE, new recommended recipe
/// might be selected and we do not want that while user is looking at the recommended recipe
void Data::SetRecommendedRecipe()
{
    for(auto const &ent1 : mapOfUsersAndRecipesTheyLiked)
    {
        for(auto const &ent2 : ent1.second)
        {
            if(ent2->GetRecipeId() == idOfRecommendedRecipe)
            {
                this->recommendedRecipe = ent2;
            }
        }
    }
}

/// menu vector is cleared and recipes are added first and beverages second
void Data::UpdateMenu(const vector <string> &recipes, const vector <string> &beverages)
{
    this->menu.clear();
    for(unsigned int i = 0; i < recipes.size(); ++i)
    {
        this->menu.push_back(recipes[i]);
    }
    for(unsigned int i = 0; i < beverages.size(); ++i)
    {
        this->menu.push_back(beverages[i]);
    }
}

int Data::GetRecipeIDBasedOnPositionInMenu(const int &index)
{
    auto it = this->mapOfRecipesInMenu.find(this->user->GetUserId());
    int id = it->second[index]->GetRecipeId();
    delete it->second[index];
    it->second.erase(it->second.begin() + index);
    return id;
}

///DO NOT delete recommended recipe as it points to recipe in vector of recipes which will deleted separately
Data::Data()
{
    user = NULL;
    recipe = NULL;
    recommendedRecipe = NULL;
}

///deletes User*
Data::~Data()
{
    delete user;
    DeleteMap(mapOfUsersAndRecipesTheyLiked);
    DeleteMap(mapOfRecipesInMenu);
}