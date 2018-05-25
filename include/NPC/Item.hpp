//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include <string>

namespace RG{
    namespace NPC{
        ///object containing ID, type, rarity and name of the item
        class Item{
        public:
            Item(int id, int idType, int rarity, std::string name);
            ~Item();
            int GetId();
            int GetIdType();
            int GetRarity();
            std::string GetName();
        protected:
        private:
            int id;
            int idType;
            int rarity;
            std::string name;
        };
    }
}

#endif //GAME_ITEM_HPP
