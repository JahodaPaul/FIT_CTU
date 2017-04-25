//
// Created by pjahoda on 4/21/17.
//

#ifndef RECIPE_MANAGER_DATA_H
#define RECIPE_MANAGER_DATA_H

#include "Connection.h"
#include <set>
#include <iostream>

class Data : public Connection
{
public:
    Data();
    void GetDataFromDatabase();
protected:
private:
    void CopyIntoMap(pqxx::result,string);
    map<string,string> foodNameAndCategory;
    void printWaitDownloading(int dots);

    struct Recipe
    {
        Recipe(vector<string> ingridients, vector<int> ingridientWeight,bool containsMeat, bool containsSecondVegetable, bool containsNuts)
        {
            this->ingridients=ingridients;
            this->ingridientWeight=ingridientWeight;
            this->containsMeat=containsMeat;
            this->containsSecondVegetable=containsSecondVegetable;
            this->containsNuts=containsNuts;
            this->numberOfIngridients= (int) this->ingridients.size();
        }
        bool operator==(Recipe & r)
        {
            if(r.numberOfIngridients!=this->numberOfIngridients)
            {
                return false;
            }
            for(int i=0;i<this->numberOfIngridients;i++)
            {
                if(this->ingridients[i]!=r.ingridients[i])
                {
                    return false;
                }
                if(this->ingridientWeight[i]!=r.ingridientWeight[i])
                {
                    return false;
                }
            }
            return true;
        }
        vector<string> ingridients;
        vector<int> ingridientWeight;
        bool containsMeat;
        bool containsSecondVegetable;
        bool containsNuts;
        int numberOfIngridients;
    };
    vector<Recipe> vectorOfRecipes;

};

#endif //RECIPE_MANAGER_DATA_H
