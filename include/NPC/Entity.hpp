//
// Created by pjahoda on 4.5.18.
//

#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <memory>

#include "NPC/Intelligence.hpp"

namespace RG{
    namespace NPC{
        class Entity{
        public:
        protected:
        private:
            std::shared_ptr<RG::NPC::Intelligence> intelligence;
        };
    }
}

#endif //GAME_ENTITY_HPP
