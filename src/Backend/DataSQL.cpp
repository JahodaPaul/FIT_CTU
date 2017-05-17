//
// Created by Pavel on 5/17/2017.
//

#include "DataSQL.h"

/**
   copy food ingredients into map, key is its name and values is its category - name of a category is a name of column in recipes table
   careful, vegetables has two columns vegetable and vegetable2, so does spices - spice and spice2
   integer parameter is used to show progressBar progress
 * @param select
 * DO NOT CHANGE CASE 14
 */
void DataSQL::GetDataFromDatabase(const int select)
{
    string idString="";
    int tmp=0;
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
        case 16:
            r = query("SELECT * FROM \"public\".\"recipes\" JOIN \"public\".\"recipesMenu\" ON id=id_recipes;");
            CopyIntoMapRecipes(r, mapOfRecipesInMenu);
            break;
        case 17:
            r = query("SELECT * FROM \"public\".\"vegetables\"");
            CopyIntoMap(r, "vegetable", foodNameAndCategory);
            break;
        case 18:
            tmp = this->user->GetUserId();
            idString = to_string(tmp);
            r = query("SELECT * FROM \"public\".\"beverages_menu\" WHERE id_user="+idString+";");
            GetDataFromMenuTable(r,menu,recipesMenu,beveragesMenu);
            break;
        default:
            /* Blok default */
            break;
    }
}

///copies ingredient name from pqxx::result as a key and ingredient category as value into the map
void DataSQL::CopyIntoMap(const result &R, const string category, map <string, string> &myMap)
{
    for(result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
        myMap.insert(make_pair(c[1].as<string>(), category));
    }
}

///copies recipes into map where key is user id and value is vector of recipes
void DataSQL::CopyIntoMapRecipes(const pqxx::result &R, map<int, vector<Recipe *> > &myMap)
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
 * gets recipes from database and inserts into vector these new recipes, also creates string for each recipe and adds
 * it into vector of strings which is later used into WINDOW box
 * @param selectedIngredients
 */
void DataSQL::GetRecipesBySelectedIngredients(const vector <string> &selectedIngredients)
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

/// checks if recipe is already liked by this user, if not insert like into database
void DataSQL::LikeRecipe(const int &userID, const Recipe *currentRecipe)
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
void DataSQL::UnlikeRecipe(const int &userID, const Recipe *currentRecipe)
{
    int recipeID = currentRecipe->GetRecipeId();
    int tmp = userID;
    string UserIDString = to_string(tmp);
    string recipeIDString = to_string(recipeID);
    query("DELETE FROM \"public\".\"recipesUsersLiked\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
}

///TODO METHODS
void DataSQL::AddBeverageToMenuTable(const int &userId, const string &name)
{
    int tmp = userId;
    string UserIDString = to_string(tmp);
    query("INSERT INTO \"public\".\"beverages_menu\" (id,id_user,name_beverage) VALUES(nextval('id_beveragesmenu'),'" +
          UserIDString + "','" + name + "')");
}

void DataSQL::DeleteBeverageFromMenuTable(const int &userId, const string &name)
{
    int tmp = userId;
    string UserIDString = to_string(tmp);
    query("DELETE FROM \"public\".\"beverages_menu\" WHERE name_beverage='" + name + "' AND id_user=" + UserIDString + ";");
}

void DataSQL::AddRecipeToMenuTable(const int &userID, const int &toBeAddedRecipeID)
{
    int tmp = userID;
    string UserIDString = to_string(tmp);
    tmp = toBeAddedRecipeID;
    string recipeIDString = to_string(tmp);
    pqxx::result R = query(
            "SELECT * FROM \"public\".\"recipesMenu\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
    if(R.size() == 0)
    {
        query("INSERT INTO \"public\".\"recipesMenu\" (id_recipesmenu,id_recipes,id_user) VALUES(nextval('id_recipesmenu'),'" +
              recipeIDString + "','" + UserIDString + "')");
    }
}

void DataSQL::DeleteRecipeFromMenuTable(const int &userID, const int &toBeDeletedRecipeID)
{
    int tmp = userID;
    string UserIDString = to_string(tmp);
    tmp = toBeDeletedRecipeID;
    string recipeIDString = to_string(tmp);
    query("DELETE FROM \"public\".\"recipesMenu\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
}

void DataSQL::GetDataFromMenuTable(const result &R, vector <string> &menu, vector<string> &recipesMenu, vector<string> &beveragesMenu)
{
    int userID = this->user->GetUserId();
    for(auto const &ent1 : mapOfRecipesInMenu)
    {
        if(ent1.first==userID)
        {
            for(auto const &ent2 : ent1.second)
            {
                this->recipesMenu.push_back(ent2->ToString(screenWidth));
                this->menu.push_back(this->recipesMenu.back());
            }
        }
    }
    for(result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
        this->beveragesMenu.push_back(c[1].as<string>());
        this->menu.push_back(this->beveragesMenu.back());
    }
}

DataSQL::DataSQL()
{

}

DataSQL::~DataSQL()
{

}