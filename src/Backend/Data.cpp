//
// Created by pjahoda on 4/21/17.
//

#include "Data.h"
#include <iostream>

Data::Data() {
    user=NULL;
}

///deletes User*
Data::~Data()
{
    delete user;
}

/**
   copy food ingredients into map, key is its name and values is its category - name of a category is a name of column in recipes table
   careful, vegetables has two columns vegetable and vegetable2, so does spices - spice and spice2
   integer parameter is used to show progressBar progress
 * @param select
 */
void Data::GetDataFromDatabase(const int select)
{

    result r;
    switch(select)
    {
        case 1:
            r = query("SELECT * FROM \"public\".\"alcoholicBeverages\"");
            CopyIntoMap(r,".alcB",beveragesAndCategory);
            break;
        case 2:

            break;
        case 3:
            r = query("SELECT * FROM \"public\".\"beverages\"");
            CopyIntoMap(r,".bev",beveragesAndCategory);
            break;
        case 4:

            break;
        case 5:
            r = query("SELECT * FROM \"public\".\"cheese\"");
            CopyIntoMap(r,"cheese",foodNameAndCategory);
            break;
        case 6:

            break;
        case 7:
            r = query("SELECT * FROM \"public\".\"fruit\"");
            CopyIntoMap(r,"fruit",foodNameAndCategory);
            break;
        case 8:

            break;
        case 9:
            r = query("SELECT * FROM \"public\".\"meat\"");
            CopyIntoMap(r,"meat",foodNameAndCategory);
        case 10:

            break;
        case 11:
            r = query("SELECT * FROM \"public\".\"nuts\"");
            CopyIntoMap(r,"nuts",foodNameAndCategory);
            break;
        case 12:

            break;
        case 13:
            r = query("SELECT * FROM \"public\".\"sides\"");
            CopyIntoMap(r,"side",foodNameAndCategory);
            break;
        case 14:
            r = query("SELECT * FROM \"public\".\"recipes\" JOIN \"public\".\"recipesUsersLiked\" ON id=id_recipes;");
            CopyIntoMapRecipes(r,mapOfUsersAndRecipesTheyLiked);
            break;
        case 15:
            r = query("SELECT * FROM \"public\".\"spices\"");
            CopyIntoMap(r,"spice2",foodNameAndCategory);
            break;
        case 16:

            break;
        case 17:
            r = query("SELECT * FROM \"public\".\"vegetables\"");
            CopyIntoMap(r,"vegetable",foodNameAndCategory);
            break;
        case 18:

            break;
        default:
            /* Blok default */
            break;
    }
}

///copies ingredient name from pqxx::result as a key and ingredient category as value into the map
void Data::CopyIntoMap(const result &R,const string category, map<string,string> & myMap)
{
    for (result::const_iterator c = R.begin(); c != R.end(); ++c)
    {
        myMap.insert(make_pair(c[1].as<string>(),category));
    }
}

/**
 * \return map foodNameAndCategory
 */
map<string, string> &Data::GetMapOfIngridients()
{
    return foodNameAndCategory;
}

///copies recipes into map where key is user id and value is vector of recipes
void Data::CopyIntoMapRecipes(const pqxx::result &R,map<int,vector<Recipe *> > & myMap)
{
    for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
        vector<string> ingredients;
        vector<int> weights;

        for(int j=1;j<10;++j) {
            ingredients.push_back(c[j].as<string>());
        }
        for(int j=10;j<19;++j) {
            weights.push_back(c[j].as<int>());
        }
        int idRecipe = c[20].as<int>();
        int id = c[21].as<int>();
        auto it = myMap.find(id);

        if(it==myMap.end()) {
            myMap.insert(make_pair(id,vector<Recipe*>()));
            auto it2 = myMap.find(id);
            (*it2).second.push_back(new Recipe(ingredients,weights,idRecipe));
        }
        else {
            (*it).second.push_back(new Recipe(ingredients,weights,idRecipe));
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
Recipe& Data::GetRecommendedRecipe(const Recipe &recipe, const int userID)
{
    int max=0;
    typedef map<int, vector<Recipe *> >::iterator it_type;
    it_type it;
    for(it_type iterator = mapOfUsersAndRecipesTheyLiked.begin(); iterator != mapOfUsersAndRecipesTheyLiked.end(); ++iterator){
        if((*iterator).first== userID)
        {
            continue;
        }
        int sum=0,average=0;
        for(unsigned int j=0;j<(*iterator).second.size();j++)
        {
            sum+=(*iterator).second[j]->HowMuchAreRecipesSame(recipe);
        }
        average=sum/(int)(*iterator).second.size();
        cout << average << endl;
        if(average>max)
        {
            max=average;
            it=iterator;
        }
    };

    max=0;
    Recipe * p;
    for(unsigned int j=0;j<(*it).second.size();j++)
    {
        if((*it).second[j]->HowMuchAreRecipesSame(recipe) > max)
        {
            max=(*it).second[j]->HowMuchAreRecipesSame(recipe);
            p=(*it).second[j];
        }
    }
    return (*p);
}

/// \return pointer to a user
User * Data::GetUser()
{
    return this->user;
}

/// creates a user if it does not exist
void Data::CreateNewUser(User * user1)
{
    if(this->user==NULL)
    {
        this->user=user1;
    }
}