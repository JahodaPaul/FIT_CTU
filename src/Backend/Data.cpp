//
// Created by pjahoda on 4/21/17.
//

#include "Data.h"
#include <iostream>

///same purpose as SetRecommendedRecipe function, when user presses LIKE/UNLIKE its value is nonzero, else it is zero
int Data::idOfRecommendedRecipe = 0;

/**
   copy food ingredients into map, key is its name and values is its category - name of a category is a name of column in recipes table
   careful, vegetables has two columns vegetable and vegetable2, so does spices - spice and spice2
   integer parameter is used to show progressBar progress
 * @param select
 * DO NOT CHANGE CASE 14
 */
void Data::GetDataFromDatabase(const int select)
{

    result r;
    switch(select)
    {
        //UNCOMMENT WHEN DONE TESTING
        case 1:
            r = query("SELECT * FROM \"public\".\"alcoholicBeverages\"");
            CopyIntoMap(r, ".alcB", beveragesAndCategory);
            break;
//        case 2:
//
//            break;
//        case 3:
//            r = query("SELECT * FROM \"public\".\"beverages\"");
//            CopyIntoMap(r, ".bev", beveragesAndCategory);
//            break;
//        case 4:
//
//            break;
//        case 5:
//            r = query("SELECT * FROM \"public\".\"cheese\"");
//            CopyIntoMap(r, "cheese", foodNameAndCategory);
//            break;
//        case 6:
//
//            break;
//        case 7:
//            r = query("SELECT * FROM \"public\".\"fruit\"");
//            CopyIntoMap(r, "fruit", foodNameAndCategory);
//            break;
//        case 8:
//
//            break;
//        case 9:
//            r = query("SELECT * FROM \"public\".\"meat\"");
//            CopyIntoMap(r, "meat", foodNameAndCategory);
//        case 10:
//
//            break;
//        case 11:
//            r = query("SELECT * FROM \"public\".\"nuts\"");
//            CopyIntoMap(r, "nuts", foodNameAndCategory);
//            break;
//        case 12:
//
//            break;
//        case 13:
//            r = query("SELECT * FROM \"public\".\"sides\"");
//            CopyIntoMap(r, "side", foodNameAndCategory);
//            break;
        case 14:
            r = query("SELECT * FROM \"public\".\"recipes\" JOIN \"public\".\"recipesUsersLiked\" ON id=id_recipes;");
            CopyIntoMapRecipes(r, mapOfUsersAndRecipesTheyLiked);
            break;
//        case 15:
//            r = query("SELECT * FROM \"public\".\"spices\"");
//            CopyIntoMap(r, "spice2", foodNameAndCategory);
//            break;
//        case 16:

            break;
        case 17:
            r = query("SELECT * FROM \"public\".\"vegetables\"");
            CopyIntoMap(r, "vegetable", foodNameAndCategory);
            break;
        case 18:

            break;
        default:
            /* Blok default */
            break;
    }
}

///copies ingredient name from pqxx::result as a key and ingredient category as value into the map
void Data::CopyIntoMap(const result &R, const string category, map <string, string> &myMap)
{
    for(result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
        myMap.insert(make_pair(c[1].as<string>(), category));
    }
}

/**
 * \return map foodNameAndCategory
 */
map <string, string> &Data::GetMapOfIngridients()
{
    return foodNameAndCategory;
}

/// \return map beveragesAndCategory
map <string, string>& Data::GetMapOfBeverages()
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

///copies recipes into map where key is user id and value is vector of recipes
void Data::CopyIntoMapRecipes(const pqxx::result &R, map<int, vector<Recipe *> > &myMap)
{
    for(result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
        vector <string> ingredients;
        vector<int> weights;

        for(int j = 1; j < 10; ++j)
        {
            ingredients.push_back(c[j].as<string>());
        }
        for(int j = 10; j < 19; ++j)
        {
            weights.push_back(c[j].as<int>());
        }
        int idRecipe = c[20].as<int>();
        int id = c[21].as<int>();
        auto it = myMap.find(id);

        if(it == myMap.end())
        {
            myMap.insert(make_pair(id, vector<Recipe *>()));
            auto it2 = myMap.find(id);
            (*it2).second.push_back(new Recipe(ingredients, weights, idRecipe));
        }
        else
        {
            (*it).second.push_back(new Recipe(ingredients, weights, idRecipe));
        }
    }
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
        average = sum / (int) (*iterator).second.size();
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

/**
 * gets recipes from database and inserts into vector these new recipes, also creates string for each recipe and adds
 * it into vector of strings which is later used into WINDOW box
 * @param selectedIngredients
 */
void Data::GetRecipesBySelectedIngredients(const vector <string> &selectedIngredients)
{
    int index = 0;
    string indexString = "";
    //SQL statement-----------------------------------------------------------------------------------------------------
    string sql = "SELECT * FROM \"public\".\"recipes\" ";
    if(selectedIngredients.size() >= 1)
    {
        sql += "WHERE ";
    }
    unsigned int cnt = 0;
    for(const string &ingredient : selectedIngredients)
    {
        cnt++;
        if(cnt > 1)
        {
            sql += "AND ";
        }
        auto it = foodNameAndCategory.find(ingredient);
        if(it != foodNameAndCategory.end())
        {
            if(it->second == "vegetable")
            {
                sql += '(';
                sql += it->second;
                sql += '=';
                sql += "'";
                sql += it->first;
                sql += "' ";
                sql += "OR ";

                sql += "vegetable2";
                sql += '=';
                sql += "'";
                sql += it->first;
                sql += "') ";

            }
            else
            {
                sql += it->second;
                sql += '=';
                sql += "'";
                sql += it->first;
                sql += "' ";
            }
        }
    }
    sql += "LIMIT 100";
    result R = query(sql);
    //------------------------------------------------------------------------------------------------------------------
    //getting recipes into vector of recipes and map of strings---------------------------------------------------------
    for(result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
        vector <string> ingredients;
        vector<int> weights;
        int idRecipe = c[0].as<int>();
        for(int j = 1; j < 10; ++j)
        {
            ingredients.push_back(c[j].as<string>());
        }
        for(int j = 10; j < 19; ++j)
        {
            weights.push_back(c[j].as<int>());
        }
        recipesSelectByIngredients.push_back(new Recipe(ingredients, weights, idRecipe));
        string recipeString = recipesSelectByIngredients.back()->ToString(this->screenWidth);
        indexString = to_string(index);
        recipesString.insert(make_pair(recipeString, indexString));
        index++;
    }
    //------------------------------------------------------------------------------------------------------------------
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

/// checks if recipe is already liked by this user, if not insert like into database
void Data::LikeRecipe(const int &userID, const Recipe *currentRecipe)
{
    int recipeID = currentRecipe->GetRecipeId();
    int tmp = userID;
    string UserIDString = to_string(tmp);
    string recipeIDString = to_string(recipeID);
    pqxx::result R = query(
            "SELECT * FROM \"public\".\"recipesUsersLiked\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
    if(R.size() == 0)
    {
        query("INSERT INTO \"public\".\"recipesUsersLiked\" (id_recipeslike,id_recipes,id_user) VALUES(nextval('id_recipeslikeserial'),'" +
              recipeIDString + "','" + UserIDString + "')");
    }
}

/// deletes row in database that based on userID and recipeID
void Data::UnlikeRecipe(const int &userID, const Recipe *currentRecipe)
{
    int recipeID = currentRecipe->GetRecipeId();
    int tmp = userID;
    string UserIDString = to_string(tmp);
    string recipeIDString = to_string(recipeID);
    query("DELETE FROM \"public\".\"recipesUsersLiked\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
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
    int result=0;
    for(auto const &ent1 : mapOfUsersAndRecipesTheyLiked)
    {
        if(ent1.first==userID)
        {
            result=(int)ent1.second.size();
            return result;
        }
    }
    return result;
}

///frees Recipe * and clears map
void Data::DeleteMapOfUsersAndRecipesTheyLiked()
{
    for(auto &ent1 : mapOfUsersAndRecipesTheyLiked)
    {
        for(auto &ent2 : ent1.second)
        {
            delete ent2;
        }
        ent1.second.clear();
    }
    mapOfUsersAndRecipesTheyLiked.clear();
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

///TODO METHODS
void Data::AddBeverageToMenuTable(const int &userId, const string &name)
{

}

void Data::DeleteBeverageFromMenuTable(const int &userId, const string &name)
{

}

void Data::AddRecipeToMenuTable(const int &userID, const int &toBeAddedRecipeID)
{

}

void Data::DeleteRecipeFromMenuTable(const int &userID, const int &toBeDeletedRecipeID)
{

}

void Data::GetDataFromMenuTable(const int &userID, vector <string> &menu)
{

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
    DeleteMapOfUsersAndRecipesTheyLiked();
}