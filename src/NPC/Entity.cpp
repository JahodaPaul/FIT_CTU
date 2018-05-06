//
// Created by pjahoda on 4.5.18.
//

#include "NPC/Entity.hpp"

namespace RG{
    namespace NPC{

        Entity::Entity(int startGold, std::shared_ptr<RG::NPC::Intelligence> intelligence, int entityId,  bool isPlayer, bool questNPCOnly) {
            this->gold = startGold;
            this->intelligence = intelligence;
            this->entityId = entityId;
            this->isPlayer = isPlayer;
            this->questNPCOnly = questNPCOnly;
        }

        Entity::~Entity() {

        }

        void Entity::AddMoney(int money) {
            this->gold += money;
        }

        void Entity::Work() {
            this->itemIOwn->push_back(this->itemToCreate);
        }

        bool Entity::IsPlayer() const{
            return this->isPlayer;
        }

        std::shared_ptr<RG::NPC::Intelligence> Entity::GetIntelligence(){
            return this->intelligence;
        }

        void Entity::SetItem(std::shared_ptr<RG::NPC::Item> item) {
            this->itemToCreate = item;
        }

        std::shared_ptr< std::vector<std::shared_ptr<RG::NPC::Item>> > Entity::GetItemsIOwn(){
            return this->itemIOwn;
        }
    }
}
