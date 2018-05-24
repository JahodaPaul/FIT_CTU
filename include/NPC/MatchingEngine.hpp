//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_MATCHINGENGINE_HPP
#define GAME_MATCHINGENGINE_HPP

#include <map>
#include <vector>
#include <algorithm>

#include "NPC/Request.hpp"
#include "Util/Subject.hpp"

namespace RG{
    namespace NPC{
        class MatchingEngine : public Util::Subject {
        public:
            MatchingEngine();
            ~MatchingEngine();
            void Match(std::map<int,std::vector<Request> > & offers, std::map<int,std::vector<Request> > & demands);
            const std::string & getOutput() const;
        protected:
        private:
            static bool Ascending(const Request & a, const Request & b);
            static bool Descending(const Request & a, const Request & b);
            int MatchingPrice(int priceOfferedForItem, int priceDemandedForItem);
            std::string m_output;
        };
    }
}

#endif //GAME_MATCHINGENGINE_HPP
