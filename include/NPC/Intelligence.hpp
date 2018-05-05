//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_INTELLIGENCE_HPP
#define GAME_INTELLIGENCE_HPP

#include <map>
#include <vector>

// #include "NPC/Request.hpp"

namespace RG{
    namespace NPC{

        class Request;

        class Intelligence{
        public:
            Intelligence();
            virtual ~Intelligence();
            virtual std::map<int,std::vector<Request> > & BuyOrSell(std::map<int,std::vector<Request> > offers, std::map<int,std::vector<Request> > demands) const = 0;
        protected:
        private:
        };
    }
}

#endif //GAME_INTELLIGENCE_HPP
