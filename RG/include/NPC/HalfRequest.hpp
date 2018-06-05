//
// Created by pjahoda on 6.5.18.
//

#ifndef GAME_HALFREQUEST_HPP
#define GAME_HALFREQUEST_HPP

#include <memory>

#include "NPC/Item.hpp"

namespace RG{
    namespace NPC{
        //! \class HalfRequest
        /*!
         * \brief
         * class used as a order or demand in the matchingEngine class
         */
        class HalfRequest{
        public:
            HalfRequest(){
            }
            ///Object containing - NPC::Item, price and whether to buy or sell said item
            HalfRequest(std::shared_ptr<RG::NPC::Item> _item, int _price, bool _buy){
                item = _item;
                price = _price;
                buy = _buy;
            }
            ~HalfRequest(){

            }
            std::shared_ptr<RG::NPC::Item> item;
            int price;
            bool buy;
        };
    }
}

#endif //GAME_HALFREQUEST_HPP
