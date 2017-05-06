//
// Created by pjahoda on 4/20/17.
//

#include "User.h"


User::User(int id,string name){
    this->id=id;
    this->name=name;
}

/// \return integer user id
int User::GetUserId()
{
    return this->id;
}