//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <memory>
#include <string>

#include "NPC/BasicIntelligence.hpp"
#include "NPC/Item.hpp"

namespace RG{
    namespace NPC{

        //! \class Entity
        /*!
         * \brief
         * An object with distinct and independent existence.
         */
        class Entity{
        public:
            Entity(std::string name, int startGold, std::shared_ptr<RG::NPC::Intelligence> intelligence, int entityId, bool isPlayer=false, bool questNPCOnly=false,int inventorySize = 5);
            virtual ~Entity();
            ///create NPC::Item
            void Work();
            void AddMoney(int money);
            void SubtractMoney(int money);


            void Taxes(int money){};//TODO LATER

            ///whether entity is character controlled by person behind the computer or not
            bool IsPlayer() const;
            std::shared_ptr<RG::NPC::Intelligence> GetIntelligence();
            void SetItem(std::shared_ptr<RG::NPC::Item> item);

            std::shared_ptr< std::vector<std::shared_ptr<RG::NPC::Item>> > GetItemsIOwn();

            ///Function for matching engine, for buying NPC::Item
            void AddItem(std::shared_ptr<RG::NPC::Item> );
            ///Function for matching engine, for selling NPC::Item
            void DeleteItemBasedOnID(int id);

            std::string GetName();
            int GetGold();
        protected:
            std::shared_ptr<RG::NPC::Intelligence> intelligence;
            int gold;
            int entityId;
            int inventorySize;
            std::string name;

            std::shared_ptr<RG::NPC::Item> itemToCreate;
            std::shared_ptr< std::vector<std::shared_ptr<RG::NPC::Item>> > itemIOwn;

            bool isPlayer;
            bool questNPCOnly;
        private:
        };
    }
}

#endif //GAME_ENTITY_HPP
