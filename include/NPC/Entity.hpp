//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <memory>

#include "NPC/Intelligence.hpp"
#include "NPC/Item.hpp"

namespace RG{
    namespace NPC{
        class Entity{
        public:
            Entity(int startGold, std::shared_ptr<RG::NPC::Intelligence> intelligence, int entityId, bool isPlayer=false, bool questNPCOnly=false);
            virtual ~Entity();
            void Work();
            void AddMoney(int money);
            void Taxes(int money){};//TODO LATER
            bool IsPlayer() const;
            std::shared_ptr<RG::NPC::Intelligence> GetIntelligence();
            void SetItem(std::shared_ptr<RG::NPC::Item> item);
            std::shared_ptr< std::vector<std::shared_ptr<RG::NPC::Item>> > GetItemsIOwn();
        protected:
            std::shared_ptr<RG::NPC::Intelligence> intelligence;
            int gold;
            int entityId;
            std::shared_ptr<RG::NPC::Item> itemToCreate;
            std::shared_ptr< std::vector<std::shared_ptr<RG::NPC::Item>> > itemIOwn;

            bool isPlayer;
            bool questNPCOnly;
        private:
        };
    }
}

#endif //GAME_ENTITY_HPP
