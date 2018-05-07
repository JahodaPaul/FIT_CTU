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
        class Entity{
        public:
            Entity(std::string name, int startGold, std::shared_ptr<RG::NPC::Intelligence> intelligence, int entityId, bool isPlayer=false, bool questNPCOnly=false,int inventorySize = 5);
            virtual ~Entity();
            void Work();
            void AddMoney(int money);
            void SubtractMoney(int money);


            void Taxes(int money){};//TODO LATER
            bool IsPlayer() const;
            std::shared_ptr<RG::NPC::Intelligence> GetIntelligence();
            void SetItem(std::shared_ptr<RG::NPC::Item> item);
            std::shared_ptr< std::vector<std::shared_ptr<RG::NPC::Item>> > GetItemsIOwn();

            void AddItem(std::shared_ptr<RG::NPC::Item> );
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
