//
// Created by pjahoda on 4.5.18.
//

#include "NPC/Item.hpp"

RG::NPC::Item::~Item() {

}

RG::NPC::Item::Item(int id, int idType, int rarity, std::string name) {

}

int RG::NPC::Item::GetId() {
    return this->id;
}

int RG::NPC::Item::GetIdType() {
    return this->idType;
}

int RG::NPC::Item::GetRarity() {
    return this->rarity;
}

std::string RG::NPC::Item::GetName() {
    return this->name;
}
