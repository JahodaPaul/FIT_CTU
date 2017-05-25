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
    string idString = "";
    int tmp = 0;
    PGresult * r;
    switch(select)
    {
        case 1:
            r = query("SELECT * FROM \"public\".\"alcoholicBeverages\"");
            CopyIntoMap(r, ".alcB", beveragesAndCategory);
            PQclear(r);
            break;
        case 2:

            break;
        case 3:
            r = query("SELECT * FROM \"public\".\"beverages\"");
            CopyIntoMap(r, ".bev", beveragesAndCategory);
            PQclear(r);
            break;
        case 4:

            break;
        case 5:
            r = query("SELECT * FROM \"public\".\"cheese\"");
            CopyIntoMap(r, "cheese", foodNameAndCategory);
            PQclear(r);
            break;
        case 6:

            break;
        case 7:
            r = query("SELECT * FROM \"public\".\"fruit\"");
            CopyIntoMap(r, "fruit", foodNameAndCategory);
            PQclear(r);
            break;
        case 8:

            break;
        case 9:
            r = query("SELECT * FROM \"public\".\"meat\"");
            CopyIntoMap(r, "meat", foodNameAndCategory);
            PQclear(r);
        case 10:

            break;
        case 11:
            r = query("SELECT * FROM \"public\".\"nuts\"");
            CopyIntoMap(r, "nuts", foodNameAndCategory);
            PQclear(r);
            break;
        case 12:

            break;
        case 13:
            r = query("SELECT * FROM \"public\".\"sides\"");
            CopyIntoMap(r, "side", foodNameAndCategory);
            PQclear(r);
            break;
        case 14:
            r = query("SELECT * FROM \"public\".\"recipes\" JOIN \"public\".\"recipesUsersLiked\" ON id=id_recipes;");
            CopyIntoMapRecipes(r, mapOfUsersAndRecipesTheyLiked);
            PQclear(r);
            break;
        case 15:
            r = query("SELECT * FROM \"public\".\"spices\"");
            CopyIntoMap(r, "spice2", foodNameAndCategory);
            PQclear(r);
            break;
        case 16:
            r = query("SELECT * FROM \"public\".\"recipes\" JOIN \"public\".\"recipesMenu\" ON id=id_recipes;");
            CopyIntoMapRecipes(r, mapOfRecipesInMenu);
            PQclear(r);
            break;
        case 17:
            r = query("SELECT * FROM \"public\".\"vegetables\"");
            CopyIntoMap(r, "vegetable", foodNameAndCategory);
            PQclear(r);
            break;
        case 18:
            tmp = this->user->GetUserId();
            idString = to_string(tmp);
            r = query("SELECT * FROM \"public\".\"beverages_menu\" WHERE id_user=" + idString + ";");
            GetDataFromMenuTable(r, menu, recipesMenu, beveragesMenu);
            PQclear(r);
            break;
        default:
            /* Blok default */
            break;
    }

}

///copies ingredient name from pqxx::result as a key and ingredient category as value into the map
void DataSQL::CopyIntoMap(const PGresult * R, const string category, map <string, string> &myMap)
{
    int rows = PQntuples(R);
    for(int i=0; i<rows; ++i)
    {
        string tmp = PQgetvalue(R, i, 1);
        myMap.insert(make_pair(tmp, category));
    }
}

///copies recipes into map where key is user id and value is vector of recipes
void DataSQL::CopyIntoMapRecipes(const PGresult *R, map<int, vector<Recipe *> > &myMap)
{
    int rows = PQntuples(R);
    for(int i=0; i<rows; ++i)
    {
        vector <string> ingredients;
        vector<int> weights;
        for(int j = 1; j < 10; ++j)
        {
            string tmp = PQgetvalue(R, i, j);
            ingredients.push_back(tmp);
        }
        for(int j = 10; j < 19; ++j)
        {
            string tmp = PQgetvalue(R, i, j);
            int weight  = atoi( tmp.c_str() );
            weights.push_back(weight);
        }
        string tmp = PQgetvalue(R, i, 20);
        int idRecipe = atoi( tmp.c_str() );
        tmp = PQgetvalue(R, i, 21);
        int id = atoi( tmp.c_str() );
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
    PGresult * R = query(sql);
    //------------------------------------------------------------------------------------------------------------------
    //getting recipes into vector of recipes and map of strings---------------------------------------------------------
    int rows = PQntuples(R);
    for(int i=0; i<rows; ++i)
    {
        vector <string> ingredients;
        vector<int> weights;
        string tmp = PQgetvalue(R, i, 0);
        int idRecipe = atoi( tmp.c_str() );
        for(int j = 1; j < 10; ++j)
        {
            string tmp = PQgetvalue(R, i, j);
            ingredients.push_back(tmp);
        }
        for(int j = 10; j < 19; ++j)
        {
            string tmp = PQgetvalue(R, i, j);
            int weight  = atoi( tmp.c_str() );
            weights.push_back(weight);
        }
        recipesSelectByIngredients.push_back(new Recipe(ingredients, weights, idRecipe));
        string recipeString = recipesSelectByIngredients.back()->ToString(this->screenWidth);
        indexString = to_string(i);
        recipesString.insert(make_pair(recipeString, indexString));
    }
    PQclear(R);
    //------------------------------------------------------------------------------------------------------------------
}

/// checks if recipe is already liked by this user, if not insert like into database
void DataSQL::LikeRecipe(const int &userID, const Recipe *currentRecipe)
{
    int rows = 0;
    int recipeID = currentRecipe->GetRecipeId();
    int tmp = userID;
    string UserIDString = to_string(tmp);
    string recipeIDString = to_string(recipeID);
    PGresult * res = query(
            "SELECT * FROM \"public\".\"recipesUsersLiked\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
    if(PQresultStatus(res) == PGRES_TUPLES_OK)
    {
        rows = PQntuples(res);
    }
    if(rows==0)
    {
        query("INSERT INTO \"public\".\"recipesUsersLiked\" (id_recipeslike,id_recipes,id_user) VALUES(nextval('id_recipeslikeserial'),'" +
              recipeIDString + "','" + UserIDString + "')");
    }
    PQclear(res);
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

void DataSQL::AddRecipeToMenuTable(const int &userID, Recipe *toBeAddedRecipe)
{
    //first add to map mapOfRecipesInMenu---------------------------------------------------------------------------------------------------
    auto it = mapOfRecipesInMenu.find(userID);
    vector <string> ingredients = toBeAddedRecipe->GetIngredients();
    vector<int> weights = toBeAddedRecipe->GetIngredientWeights();
    int recipeId = toBeAddedRecipe->GetRecipeId();
    it->second.push_back(new Recipe(ingredients, weights, recipeId));
    //--------------------------------------------------------------------------------------------------------------------------------------
    int rows = 0;
    int tmp = userID;
    string UserIDString = to_string(tmp);
    tmp = toBeAddedRecipe->GetRecipeId();
    string recipeIDString = to_string(tmp);
    PGresult * res = query(
            "SELECT * FROM \"public\".\"recipesMenu\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
    if(PQresultStatus(res) == PGRES_TUPLES_OK)
    {
        rows = PQntuples(res);
    }
    if(rows==0)
    {
        query("INSERT INTO \"public\".\"recipesMenu\" (id_recipesmenu,id_recipes,id_user) VALUES(nextval('id_recipesmenu'),'" +
              recipeIDString + "','" + UserIDString + "')");
    }
    PQclear(res);
}

void DataSQL::DeleteRecipeFromMenuTable(const int &userID, const int &toBeDeletedRecipeID)
{
    int tmp = userID;
    string UserIDString = to_string(tmp);
    tmp = toBeDeletedRecipeID;
    string recipeIDString = to_string(tmp);
    query("DELETE FROM \"public\".\"recipesMenu\" WHERE id_recipes=" + recipeIDString + " AND id_user=" + UserIDString + ";");
}

void DataSQL::GetDataFromMenuTable(const PGresult *R, vector <string> &menu, vector <string> &recipesMenu, vector <string> &beveragesMenu)
{
    int userID = this->user->GetUserId();
    for(auto const &ent1 : mapOfRecipesInMenu)
    {
        if(ent1.first == userID)
        {
            for(auto const &ent2 : ent1.second)
            {
                this->recipesMenu.push_back(ent2->ToString(screenWidth));
                this->menu.push_back(this->recipesMenu.back());
            }
        }
    }
    int rows = PQntuples(R);
    for(int i=0; i<rows; ++i)
    {
        string tmp = PQgetvalue(R, i, 1);
        this->beveragesMenu.push_back(tmp);
        this->menu.push_back(this->beveragesMenu.back());
    }
}

DataSQL::DataSQL()
{

}

DataSQL::~DataSQL()
{

}