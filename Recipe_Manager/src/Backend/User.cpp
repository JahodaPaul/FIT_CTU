//
// Created by pjahoda on 4/20/17.
//

#include "User.h"


/// \return integer user id
int User::GetUserId() const
{
    return this->id;
}

/// \return name
string User::GetUserName() const
{
    return this->name;
}

User::User(const int &id, const string &name)
{
    this->id = id;
    this->name = name;
}

User::~User()
{

}