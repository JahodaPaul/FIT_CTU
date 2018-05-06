//
// Created by pjahoda on 4.5.18.
//

#include "NPC/BasicIntelligence.hpp"
#include "NPC/Request.hpp"

#include <iostream>

namespace RG{
    namespace NPC{

        BasicIntelligence::BasicIntelligence() {

        }

        BasicIntelligence::~BasicIntelligence() {

        }

        std::vector<RG::NPC::HalfRequest> BasicIntelligence::BuyOrSell(std::shared_ptr<std::vector<std::shared_ptr<RG::NPC::Item>>> itemsIOwn,
                                                                       std::map<int, std::vector<Request> > & offers,
                                                                           std::map<int, std::vector<Request> > & demands,
                                                                       std::vector<std::shared_ptr<RG::NPC::Item> > & listOfItemsPossibleToSell) {
            std::vector<RG::NPC::HalfRequest> tmp;
            int buy = (int)(std::rand() % 2);
            if(buy){
                int temporary = (int)(std::rand() % listOfItemsPossibleToSell.size());
                int randomPrice = std::rand() % 20;
                RG::NPC::HalfRequest myRequest = RG::NPC::HalfRequest(listOfItemsPossibleToSell[temporary],
                                                                      listOfItemsPossibleToSell[temporary]->GetRarity()+randomPrice,true);
                tmp.push_back(myRequest);
            }
            else{
                if(itemsIOwn->size() != 0){
                    int temporary = (int)(std::rand() % itemsIOwn->size());
                    int randomPrice = std::rand() % 10;

                    int price = (*itemsIOwn)[temporary]->GetRarity()-randomPrice >= 0 ? (*itemsIOwn)[temporary]->GetRarity()-randomPrice : 0;
                    RG::NPC::HalfRequest myRequest = RG::NPC::HalfRequest((*itemsIOwn)[temporary], price, false);
                    tmp.push_back(myRequest);
                }
            }


            return tmp;
        }
        std::shared_ptr<RG::NPC::Item> BasicIntelligence::ChooseItemToCreate(std::vector<std::shared_ptr<RG::NPC::Item>> & items,
                                                          std::map<int,std::vector<Request> > & offers,
                                                          std::map<int,std::vector<Request> > & demands){

            int temporary = (int)(std::rand() % items.size());
            return items[temporary];
        }
    }
}