//
// Created by pjahoda on 6.5.18.
//

#ifndef GAME_HALFREQUEST_HPP
#define GAME_HALFREQUEST_HPP

#include <memory>

#include "NPC/Item.hpp"

namespace RG{
    namespace NPC{
        class HalfRequest{
        public:
            HalfRequest(){
            }
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
