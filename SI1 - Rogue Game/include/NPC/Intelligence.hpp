//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_INTELLIGENCE_HPP
#define GAME_INTELLIGENCE_HPP

#include <map>
#include <vector>
#include <memory>

// #include "NPC/Request.hpp"
#include "NPC/Item.hpp"
#include "NPC/HalfRequest.hpp"

namespace RG{
    namespace NPC{

        class Request;
        //! \class Intelligence
        /*!
         * \brief
         * virtual class. Each entity has an intelligence that decides what to work on or what to sell
         */
        class Intelligence{
        public:
            Intelligence();
            virtual ~Intelligence();
            /// intelligence decides whether to buy or sell and if so what item based on function
            /// returns vector of objects containing item, price and whether to buy or sell
            virtual std::vector<RG::NPC::HalfRequest> BuyOrSell(std::shared_ptr<std::vector<std::shared_ptr<RG::NPC::Item>>>
                                                                itemsIOwn, std::map<int,std::vector<Request> > & offers,
                                                                std::map<int,std::vector<Request> > & demands,
                                                                std::vector<std::shared_ptr<RG::NPC::Item> > &, int goldEntityOwns) = 0;

            ///NPC characters are able to create items, this functions decides what items should the NPC focus on
            virtual std::shared_ptr<RG::NPC::Item> ChooseItemToCreate(std::vector<std::shared_ptr<RG::NPC::Item>> & items,
                                                                      std::map<int,std::vector<Request> > & offers,
                                                                      std::map<int,std::vector<Request> > & demands) = 0;
        protected:
        private:
        };
    }
}

#endif //GAME_INTELLIGENCE_HPP
