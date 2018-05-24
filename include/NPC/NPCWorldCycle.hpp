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


            ///Method for buying items on the market
            void Buy(std::shared_ptr<RG::NPC::Item> item, int price);

            ///Method for selling items on the market
            void Sell(std::shared_ptr<RG::NPC::Item> item, int price);

            ///What are the items currently being offered and demanded on the market
            std::pair<std::map<int,std::vector<Request> >,std::map<int,std::vector<Request> >> ReturnOffersAndDemands();

            /// returns list(vector) of items types in the game
            std::vector<std::shared_ptr<RG::NPC::Item> > ReturnItemsPossibleToBuy();

            /// returns player gold
            int ReturnPlayerGold();

            ///what items player owns
            std::shared_ptr< std::vector<std::shared_ptr<RG::NPC::Item>> > ReturnPlayerItems();

            RG::NPC::Market & getMarket();
        protected:
        private:
            std::shared_ptr<RG::NPC::Market> market;
            bool EntitiesChoseItemsToWorkOn;

            std::shared_ptr<RG::NPC::Entity> player;

        };
    }
}

#endif //GAME_NPCWORLDCYCLE_HPP
