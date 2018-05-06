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
            std::vector<RG::NPC::HalfRequest> BuyOrSell(std::shared_ptr<std::vector<std::shared_ptr<RG::NPC::Item>> > itemsIOwn,
                                                        std::map<int,std::vector<Request> > & offers,
                                                        std::map<int,std::vector<Request> > & demands,
                                                        std::vector<std::shared_ptr<RG::NPC::Item> > &);
            std::shared_ptr<RG::NPC::Item> ChooseItemToCreate(std::vector<std::shared_ptr<RG::NPC::Item>> & items,
                                                              std::map<int,std::vector<Request> > & offers,
                                                              std::map<int,std::vector<Request> > & demands);
        public:
        protected:
        private:
        };
    }
}

#endif //GAME_BASICINTELLIGENCE_HPP
