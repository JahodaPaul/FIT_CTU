//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include <string>

namespace RG{
    namespace NPC{
        //! \class Item
        /*!
         * \brief
         * Item
         */
        class Item{
        public:
            ///object containing ID, type, rarity and name of the item
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
