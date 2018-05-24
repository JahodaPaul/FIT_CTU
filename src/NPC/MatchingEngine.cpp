//
// Created by pjahoda on 4.5.18.
//

#include "NPC/MatchingEngine.hpp"
#include <iostream>

namespace RG{
    namespace NPC{

        MatchingEngine::MatchingEngine() {

        }

        MatchingEngine::~MatchingEngine() {

        }

        bool MatchingEngine::Ascending(const Request & a, const Request & b){//1,2,3
            return a.price < b.price;
        }

        bool MatchingEngine::Descending(const Request &a, const Request &b){//3,2,1
            return a.price > b.price;
        }

        int MatchingEngine::MatchingPrice(int priceOfferedForItem, int priceDemandedForItem){
            return priceDemandedForItem+priceOfferedForItem/2;
        }

        const std::string & MatchingEngine::getOutput() const {
            return m_output;
        }

        void MatchingEngine::Match(std::map<int, std::vector<Request> > &offers,
                                   std::map<int, std::vector<Request> > &demands) {

            std::map<int, std::vector<Request> >::iterator it;
            for (it = offers.begin(); it != offers.end(); it++)
            {
                auto itDemand = demands.find(it->first);
                if(itDemand != demands.end()){
                    std::sort(it->second.begin(),it->second.end(),&MatchingEngine::Ascending); //offers (selling items)
                    std::sort(itDemand->second.begin(),itDemand->second.end(),&MatchingEngine::Descending); // demands (buying items)
                    int i = 0;
                    int j = 0;
                    for(auto & offer : it->second){
                        j++;
                        if(i<(int)itDemand->second.size()){
                            if(offer.price <= itDemand->second[i].price){
                                int matchedPrice = this->MatchingPrice(itDemand->second[i].price, offer.price);

                                //std::cout << offer.player->GetName() << " sold " << offer.item->GetName() << " to " << itDemand->second[i].player->GetName() << " for " << matchedPrice << "." << std::endl;
                                m_output = offer.player->GetName() + " sold " + offer.item->GetName() + " to " + itDemand->second[i].player->GetName() + " for " + std::to_string(matchedPrice) + ".\n";
                                Notify( this, Util::Event::ITEM_SOLD );

                                //transfer items and money
                                offer.player->AddMoney(matchedPrice);
                                itDemand->second[i].player->AddItem(offer.item);
                                offer.player->DeleteItemBasedOnID(offer.item->GetId());
                                itDemand->second[i].player->SubtractMoney(matchedPrice);
                                i++;
                            }
                            else{
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }

                    for(int k=0;k<i;k++){
                        itDemand->second.front() = std::move(itDemand->second.back());
                        itDemand->second.pop_back();
                    }
                    for(int k=0;k<j;k++){
                        it->second.front() = std::move(it->second.back());
                        it->second.pop_back();
                    }

                }
            }

        }
    }
}
