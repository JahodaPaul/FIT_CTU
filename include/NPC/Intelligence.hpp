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

        class Intelligence{
        public:
            Intelligence();
            virtual ~Intelligence();
            virtual std::vector<RG::NPC::HalfRequest> BuyOrSell(std::shared_ptr<std::vector<std::shared_ptr<RG::NPC::Item>>>
                                                                itemsIOwn, std::map<int,std::vector<Request> > & offers,
                                                                std::map<int,std::vector<Request> > & demands,
                                                                std::vector<std::shared_ptr<RG::NPC::Item> > &) const = 0;
            virtual std::shared_ptr<RG::NPC::Item> ChooseItemToCreate(std::vector<std::shared_ptr<RG::NPC::Item>> & items, std::map<int,std::vector<Request> > & offers, std::map<int,std::vector<Request> > & demands) const = 0;
        protected:
        private:
        };
    }
}

#endif //GAME_INTELLIGENCE_HPP
