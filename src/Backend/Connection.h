//
// Created by Pavel on 4/16/2017.
//
#ifndef RECIPE_MANAGER_CONNECTION_H
#define RECIPE_MANAGER_CONNECTION_H

#include <iostream>
#include <string>
#include <algorithm>
#include "../../lib/libpqxx-5.0/include/pqxx/pqxx"

using namespace std;
using namespace pqxx;

class Connection
{
public:
    Connection();
    bool Connect(string,string,int &id);
    bool Register(string,string,int &id);
    result query(const string sql);
private:
    bool CheckForSQLInjection(string,string) const;

};

#endif //RECIPE_MANAGER_CONNECTION_H
