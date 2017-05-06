//
// Created by pjahoda on 4/20/17.
//

#ifndef RECIPE_MANAGER_USER_H
#define RECIPE_MANAGER_USER_H

#include <string>

using namespace std;

class User{
public:
    User();
    int GetUserId();
    void SetUserId(int);
    void SetUserName(string);
    ~User(){};
protected:
private:
    string name;
    int id;

};

#endif //RECIPE_MANAGER_USER_H
