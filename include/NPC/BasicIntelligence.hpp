//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_BASICINTELLIGENCE_HPP
#define GAME_BASICINTELLIGENCE_HPP

#include "NPC/Intelligence.hpp"

namespace RG{
    namespace NPC{
        class BasicIntelligence : Intelligence{
            BasicIntelligence();
            ~BasicIntelligence();
            std::map<int,std::vector<Request> > & BuyOrSell(std::map<int,std::vector<Request> > & offers, std::map<int,std::vector<Request> > & demands);
        public:
        protected:
        private:
        };
    }
}

#endif //GAME_BASICINTELLIGENCE_HPP
