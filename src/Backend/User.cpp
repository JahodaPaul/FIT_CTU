//
// Created by pjahoda on 4/20/17.
//

#include "User.h"


User::User(const int& id,const string& name){
    this->id=id;
    this->name=name;
}

/// \return integer user id
int User::GetUserId() const
{
    return this->id;
}