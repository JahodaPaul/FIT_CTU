//
// Created by Pavel on 4/16/2017.
//
#ifndef RECIPE_MANAGER_CONNECTION_H
#define RECIPE_MANAGER_CONNECTION_H

#include <iostream>
#include "libpqxx-5.0/include/pqxx/pqxx"

using namespace std;
using namespace pqxx;

class Connection
{
public:
    Connection();
    void Connect();
    void Disconnect();

private:
};

#endif //RECIPE_MANAGER_CONNECTION_H
