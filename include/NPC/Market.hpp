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
        protected:
        private:
            RG::NPC::MatchingEngine matchingEngine;
            std::map<int,std::vector<Request> > offers;
            std::map<int,std::vector<Request> > demands;

            std::vector<std::shared_ptr<RG::NPC::Entity> > entities;
        };
    }
}

#endif //GAME_MARKET_HPP
