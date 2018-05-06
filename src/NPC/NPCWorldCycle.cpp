//
// Created by pjahoda on 4.5.18.
//

#include <NPC/BasicIntelligence.hpp>
#include "NPC/NPCWorldCycle.hpp"

namespace RG{
    namespace NPC{

        NPCWorldCycle::NPCWorldCycle() {
            this->market = std::make_shared<RG::NPC::Market>();
            EntitiesChoseItemsToWorkOn = false;
            int startGold = 300;
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 0, 5, "bread"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 1, 10, "shoe"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 2, 2, "beer"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 3, 1000, "gold"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 4, 60, "weapon"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 5, 40, "helmet"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 6, 1, "wheat"));
            this->market->AddItem(std::make_shared<RG::NPC::Item>(0, 7, 200, "magic wand"));

            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Pavel", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 1));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Petr", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 2));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Vojta", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 3));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Vanda", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 4));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Jirka", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 5));
            this->market->AddEntity(std::make_shared<RG::NPC::Entity>("Kuba", startGold, std::make_shared<RG::NPC::BasicIntelligence>(), 6));
        }

        NPCWorldCycle::~NPCWorldCycle() {

        }

        NPCWorldCycle::NPCWorldCycle(int numberOfEntities, int numberOfGoldToBeginWith) {

        }

        void NPCWorldCycle::Run() {
            if(!EntitiesChoseItemsToWorkOn){
                this->market->EntitiesChooseFirstItemToWorkOn();
                this->EntitiesChoseItemsToWorkOn = true;
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