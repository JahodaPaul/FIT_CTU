//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_MATCHINGENGINE_HPP
#define GAME_MATCHINGENGINE_HPP

#include <map>
#include <vector>

#include "NPC/Request.hpp"

namespace RG{
    namespace NPC{
        class MatchingEngine{
        public:
            MatchingEngine();
            ~MatchingEngine();
            void Match(std::map<int,std::vector<Request> > & offers, std::map<int,std::vector<Request> > & demands);
        protected:
        private:
        };
    }
}




#endif //GAME_MATCHINGENGINE_HPP
