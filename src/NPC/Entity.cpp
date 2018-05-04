//
// Created by pjahoda on 4.5.18.
//

#include "NPC/Entity.hpp"

namespace RG{
    namespace NPC{

        Entity::Entity(int startGold, std::shared_ptr<RG::NPC::Intelligence> intelligence, int entityId, bool isPlayer,
                       bool questNPCOnly) {

        }

        Entity::~Entity() {

        }

        void Entity::AddMoney(int money) {

        }

        void Entity::Work(RG::NPC::Item &item) {

        }
    }
}
