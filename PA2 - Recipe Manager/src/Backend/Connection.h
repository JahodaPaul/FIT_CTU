//
// Created by Pavel on 4/16/2017.
//
#ifndef RECIPE_MANAGER_CONNECTION_H
#define RECIPE_MANAGER_CONNECTION_H

#include <iostream>
#include <string>
#include <algorithm>
#include "../../lib/libpq/libpq-fe.h"

using namespace std;

class Connection
{
public:
    Connection();

    ~Connection();

    bool Connect(const string &, const string &, int &id);

    bool Register(const string &, const string &, int &id);

    PGresult * query(const string sql);

private:
    bool CheckForSQLInjection(string, string) const;

};

#endif //RECIPE_MANAGER_CONNECTION_H
