//
// Created by pjahoda on 4.5.18.
//

#include "NPC/Market.hpp"

namespace RG{
    namespace NPC{
        RG::NPC::Market::Market(){

        }

        RG::NPC::Market::~Market(){

        }

        void RG::NPC::Market::AddItem(std::shared_ptr<RG::NPC::Item> item){
            this->listOfItemsPossibleToSell.push_back(item);
        }

        void RG::NPC::Market::AddEntity(std::shared_ptr<RG::NPC::Entity> entity){
            this->entities.push_back(entity);
        }

        void RG::NPC::Market::EntitiesWork(){
            for(auto & entity: this->entities){
                entity->AddMoney(5);
                if(!entity->IsPlayer()){
                    entity->Work();
                }
            }
        }

        void RG::NPC::Market::EntitiesBuyOrSell(){
            previousOffers = offers;
            previousDemands = demands;
            for(auto & entity: this->entities){
                if(!entity->IsPlayer()){
                    std::vector<HalfRequest> offersAndDemands = entity->GetIntelligence()->BuyOrSell(entity->GetItemsIOwn(),
                                                                                                     this->previousOffers,
                                                                                                     this->previousDemands,this->listOfItemsPossibleToSell, entity->GetGold());
                    for(auto & offerOrDemand : offersAndDemands){
                        RG::NPC::Request request = RG::NPC::Request(offerOrDemand.item, entity, offerOrDemand.price);
                        if(!offerOrDemand.buy){
                            auto it = this->offers.find(request.item->GetIdType());
                            if(it == this->offers.end()){
                                this->offers.insert(std::make_pair(request.item->GetIdType(),std::vector<Request>()));
                                it = this->offers.find(request.item->GetIdType());
                                it->second.push_back(request);
                            }
                            else{
                                it->second.push_back(request);
                            }
                        }
                        else{
                            auto it = this->demands.find(request.item->GetIdType());
                            if(it == this->demands.end()){
                                this->demands.insert(std::make_pair(request.item->GetIdType(),std::vector<Request>()));
                                it = this->demands.find(request.item->GetIdType());
                                it->second.push_back(request);
                            }
                            else{
                                it->second.push_back(request);
                            }
                        }

                    }
                }
            }
        }

        void RG::NPC::Market::EntitiesChooseFirstItemToWorkOn(){
            for(auto & entity: this->entities){
                std::shared_ptr<RG::NPC::Item> temporaryItem = entity->GetIntelligence()->ChooseItemToCreate(this->listOfItemsPossibleToSell,this->offers,this->demands);
                entity->SetItem(temporaryItem);
            }
        }

        void RG::NPC::Market::MatchingEngineMatch(){
            this->matchingEngine.Match(offers,demands);
        }

        std::pair<std::map<int,std::vector<Request> >,std::map<int,std::vector<Request> >> Market::ReturnOffersAndDemands() {
            return std::make_pair(this->offers,this->demands);
        }

        std::vector<std::shared_ptr<RG::NPC::Item> > Market::ReturnItemsPossibleToBuy() {
            return this->listOfItemsPossibleToSell;
        }

        void Market::Buy(std::shared_ptr<RG::NPC::Item> item, int price, std::shared_ptr<RG::NPC::Entity> player) {
            RG::NPC::Request request = RG::NPC::Request(item, player, price);
            auto it = this->demands.find(request.item->GetIdType());
            if(it == this->demands.end()){
                this->demands.insert(std::make_pair(request.item->GetIdType(),std::vector<Request>()));
                it = this->demands.find(request.item->GetIdType());
                it->second.push_back(request);
            }
            else{
                it->second.push_back(request);
            }
        }

        void Market::Sell(std::shared_ptr<RG::NPC::Item> item, int price, std::shared_ptr<RG::NPC::Entity> player) {
            RG::NPC::Request request = RG::NPC::Request(item, player, price);
            auto it = this->offers.find(request.item->GetIdType());
            if(it == this->offers.end()){
                this->offers.insert(std::make_pair(request.item->GetIdType(),std::vector<Request>()));
                it = this->offers.find(request.item->GetIdType());
                it->second.push_back(request);
            }
            else{
                it->second.push_back(request);
            }
        }

    }
}