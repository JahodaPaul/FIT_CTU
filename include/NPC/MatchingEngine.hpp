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

        //! \class MatchingEngine
        /*!
         * \brief
         * class that matches offers (entity is selling item) with demands (entity is buying item) in a stockmarket-like manner
         */
        class MatchingEngine : public Util::Subject {
        public:
            MatchingEngine();
            ~MatchingEngine();

            /// offers and demands are matched together based on price, parameters offers and demands can be changed
            void Match(std::map<int,std::vector<Request> > & offers, std::map<int,std::vector<Request> > & demands);

            /// returns message about item being bought/sold
            const std::string & getOutput() const;
        protected:
        private:

            /// for sorting offers (entites sells items) in an ascending order
            static bool Ascending(const Request & a, const Request & b);

            /// for sorting demands (entites buys items) in a descending order
            static bool Descending(const Request & a, const Request & b);

            /// return price for the item being sold
            /// if demand A > offer B (price-wise) then this function currently returns (A+B)/2
            int MatchingPrice(int priceOfferedForItem, int priceDemandedForItem);
            std::string m_output;
        };
    }
}

#endif //GAME_MATCHINGENGINE_HPP
