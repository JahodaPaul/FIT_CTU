//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_NPCWORLDCYCLE_HPP
#define GAME_NPCWORLDCYCLE_HPP

#include "NPC/Market.hpp"

namespace RG{
    namespace NPC{
        class NPCWorldCycle{
        public:
            NPCWorldCycle();
            NPCWorldCycle(int numberOfEntities, int numberOfGoldToBeginWith);
            ~NPCWorldCycle();
            void Run();

            void Buy(const RG::NPC::Item & item, int price);
            void Sell(const RG::NPC::Item & item, int price);

        protected:
        private:
            std::shared_ptr<RG::NPC::Market> market;
            bool EntitiesChoseItemsToWorkOn;

        };
    }
}

#endif //GAME_NPCWORLDCYCLE_HPP
