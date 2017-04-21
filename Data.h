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


};

#endif //RECIPE_MANAGER_DATA_H
