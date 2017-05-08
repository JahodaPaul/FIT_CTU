//
// Created by pjahoda on 5/6/17.
//

#include "Recipe.h"


/**
 * calculates percentage of same ingredients
 * @param recipe2
 * \return integer percentage
 */
int Recipe::HowMuchAreRecipesSame(const Recipe & recipe2)
{
    int percentage=0,nOfSameIngredients=0;
    for(unsigned int i=0;i<this->ingredients.size();i++)
    {
        if(i==4 || i==8)
        {
            if(i==4)
            {
                if(this->ingredients[4]==recipe2.ingredients[8] || this->ingredients[4]==recipe2.ingredients[4])
                {
                    nOfSameIngredients++;
                }
                if(this->ingredients[8]==recipe2.ingredients[8] || this->ingredients[8]==recipe2.ingredients[4])
                {
                    nOfSameIngredients++;
                    if(this->ingredients[4]==this->ingredients[8] && recipe2.ingredients[4] != recipe2.ingredients[8])
                    {
                        nOfSameIngredients--;
                    }
                }

            }
        }
        else
        {
            if(this->ingredients[i]==recipe2.ingredients[i])
            {
                nOfSameIngredients+=1;
            }
        }
    }
    percentage=(100*nOfSameIngredients)/9;
    return percentage;
}

///converts vector of ingredients into string presented to user
string Recipe::ToString(const int & screenWidth) {
    string result="";
    unsigned int cnt=0;
    for (const string& ingredient : ingredients) {
        cnt++;
        if(cnt>4 || (int)(result.length()+7+ingredient.length() ) >= screenWidth)
            return result;

        if(cnt>2 && ingredient!="#")
        {
            result+="and ";
        }
        else if(cnt==2 && ingredient!="#")
        {
            result+="with ";
        }

        if(ingredient!="#")
        {
            result+=ingredient;
            result+=' ';
        }
        else
        {
            cnt--;
        }
    }
    return result;
}

Recipe::Recipe(vector <string> ingredients, vector<int> ingredientWeight, int idRecipe)
{
    this->ingredients=ingredients;
    this->ingredientWeight=ingredientWeight;
    this->idRecipe=idRecipe;
}

Recipe::~Recipe() {

}