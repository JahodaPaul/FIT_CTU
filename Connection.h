//
// Created by Pavel on 4/16/2017.
//
#include <pqxx/pqxx>

using namespace pqxx;

#ifndef RECIPE_MANAGER_CONNECTION_H
#define RECIPE_MANAGER_CONNECTION_H

class Connection
{
public:
    Connection();
    void Connect();
    void Disconnect();

private:
};

#endif //RECIPE_MANAGER_CONNECTION_H
