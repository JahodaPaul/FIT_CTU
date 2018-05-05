//
// Created by pjahoda on 4.5.18.
//

#include "NPC/BasicIntelligence.hpp"
#include "NPC/Request.hpp"

namespace RG{
    namespace NPC{

        BasicIntelligence::BasicIntelligence() {

        }

        BasicIntelligence::~BasicIntelligence() {

        }

        std::map<int, std::vector<Request> > & BasicIntelligence::BuyOrSell(std::map<int, std::vector<Request> > & offers,
                                                                           std::map<int, std::vector<Request> > & demands) {
            std::map<int, std::vector<Request> > * tmp;//TODO
            return *tmp;
        }
    }
}