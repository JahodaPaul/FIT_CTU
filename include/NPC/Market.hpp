//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_MARKET_HPP
#define GAME_MARKET_HPP

#include "NPC/MatchingEngine.hpp"
#include "NPC/Entity.hpp"
#include "NPC/Request.hpp"

#include <memory>
#include <map>
#include <vector>

namespace RG{
    namespace NPC{
        class Market{
        public:
            Market();
            ~Market();
            ///Add new item into the game
            void AddItem(std::shared_ptr<RG::NPC::Item> item);
            ///Add new entity into the game
            void AddEntity(std::shared_ptr<RG::NPC::Entity> entity);
            void EntitiesWork();
            void EntitiesBuyOrSell();
            void EntitiesChooseFirstItemToWorkOn();

            ///calls Function Match of the class MatchingEngine
            void MatchingEngineMatch();

            /// function created for player (person behind computer)
            void Buy(std::shared_ptr<RG::NPC::Item> item, int price, std::shared_ptr<RG::NPC::Entity> player);
            /// function created for player (person behind computer)
            void Sell(std::shared_ptr<RG::NPC::Item> item, int price, std::shared_ptr<RG::NPC::Entity> player);

            std::pair<std::map<int,std::vector<Request> >,std::map<int,std::vector<Request> >> ReturnOffersAndDemands();

            ///returns every item that is defined by the game
            std::vector<std::shared_ptr<RG::NPC::Item> > ReturnItemsPossibleToBuy();

            MatchingEngine & getMatchingEngine();
        protected:
        private:
            RG::NPC::MatchingEngine matchingEngine;

            ///entity is selling item (supply)
            std::map<int,std::vector<Request> > offers;

            ///entity is buying item (demand)
            std::map<int,std::vector<Request> > demands;

            std::map<int,std::vector<Request> > previousOffers;
            std::map<int,std::vector<Request> > previousDemands;

            std::vector<std::shared_ptr<RG::NPC::Entity> > entities;
            std::vector<std::shared_ptr<RG::NPC::Item> > listOfItemsPossibleToSell;
        };
    }
}

#endif //GAME_MARKET_HPP
