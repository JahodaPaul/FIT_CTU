//
// Created by pjahoda on 4/20/17.
//

#include "User.h"


User::User(){

}

void User::SetUserId(int id)
{
    this->id=id;
}

void User::SetUserName(string name) {
    this->name=name;
}

/// \return integer user id
int User::GetUserId()
{
    return this->id;
}