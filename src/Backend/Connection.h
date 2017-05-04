//
// Created by Pavel on 4/16/2017.
//
#ifndef RECIPE_MANAGER_CONNECTION_H
#define RECIPE_MANAGER_CONNECTION_H

#include <iostream>
#include "../libpqxx-5.0/include/pqxx/pqxx"

using namespace std;
using namespace pqxx;

class Connection
{
public:
    Connection();
    bool Connect(string,string);
    bool Register(string,string);
    result query(string sql);
private:

};

#endif //RECIPE_MANAGER_CONNECTION_H
