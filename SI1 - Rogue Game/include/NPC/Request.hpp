//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_REQUEST_HPP
#define GAME_REQUEST_HPP

#include <memory>

#include "NPC/Item.hpp"
#include "Entity.hpp"

namespace RG{
    namespace NPC{
        //! \class Request
        /*!
         * \brief
         * class used by Entity to propose what the Entity wants to buy/sell
         */
        class Request{
        public:
            Request(){
            }
            ///object containing NPC::Item, price and NPC::Entity that is buying or selling said item
            Request(std::shared_ptr<RG::NPC::Item> _item, std::shared_ptr<RG::NPC::Entity> _player, int _price){
                item = _item;
                player = _player;
                price = _price;
            }
            ~Request(){

            }
            std::shared_ptr<RG::NPC::Item> item;
            std::shared_ptr<RG::NPC::Entity> player;
            int price;
        };
    }
}

#endif //GAME_REQUEST_HPP
