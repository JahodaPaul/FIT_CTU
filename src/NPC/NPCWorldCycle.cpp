//
// Created by pjahoda on 4.5.18.
//

#include <NPC/BasicIntelligence.hpp>
#include "NPC/NPCWorldCycle.hpp"

namespace RG{
    namespace NPC{

        NPCWorldCycle::NPCWorldCycle() {
            EntitiesChoseItemsToWorkOn = false;
            int startGold = 300;
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 0, 5, "bread"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 1, 10, "shoe"));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Pavel", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 1));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Petr", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 2));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Vojta", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 3));
        }

        NPCWorldCycle::~NPCWorldCycle() {

        }

        NPCWorldCycle::NPCWorldCycle(int numberOfEntities, int numberOfGoldToBeginWith) {

        }

        void NPCWorldCycle::Run() {
            if(not EntitiesChoseItemsToWorkOn){
                this->market->EntitiesChooseFirstItemToWorkOn();
            }
            this->market->EntitiesWork();
            this->market->EntitiesBuyOrSell();
            this->market->MatchingEngineMatch();
        }

        void NPCWorldCycle::Buy(const RG::NPC::Item &item, int price) {

        }

        void NPCWorldCycle::Sell(const RG::NPC::Item &item, int price) {

        }
    }
}