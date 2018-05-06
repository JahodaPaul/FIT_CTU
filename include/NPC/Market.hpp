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
            void AddItem(std::shared_ptr<RG::NPC::Item> item);
            void AddEntity(std::shared_ptr<RG::NPC::Entity> entity);
            void EntitiesWork();
            void EntitiesBuyOrSell();
            void EntitiesChooseFirstItemToWorkOn();

            void MatchingEngineMatch();

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
