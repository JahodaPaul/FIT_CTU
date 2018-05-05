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
            void Work(RG::NPC::Item & item);
            void AddMoney(int money);
            void Taxes(int money){};//TODO LATER
        protected:
            std::shared_ptr<RG::NPC::Intelligence> intelligence;
            int startGold;
            int entityId;

            bool isPlayer;
            bool questNPCOnly;
        private:
        };
    }
}

#endif //GAME_ENTITY_HPP
