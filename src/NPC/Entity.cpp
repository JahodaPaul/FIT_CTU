//
// Created by pjahoda on 4.5.18.
//

#include "NPC/Entity.hpp"

namespace RG{
    namespace NPC{

        Entity::Entity(std::string name,int startGold, std::shared_ptr<RG::NPC::Intelligence> intelligence, int entityId,  bool isPlayer, bool questNPCOnly,int inventorySize) {
            this->name = name;
            this->gold = startGold;
            this->intelligence = intelligence;
            this->entityId = entityId;
            this->isPlayer = isPlayer;
            this->questNPCOnly = questNPCOnly;
            this->inventorySize = inventorySize;
        }

        Entity::~Entity() {

        }

        void Entity::AddMoney(int money) {
            this->gold += money;
        }

        void Entity::SubtractMoney(int money) {
            this->gold -= money;
        }

        void Entity::Work() {
            if((int)this->itemIOwn->size() < this->inventorySize){
                this->itemIOwn->push_back(this->itemToCreate);
            }
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

        void Entity::DeleteItemBasedOnID(int id){
            //TODO there is really no concept of unique IDs NPC namespace :D
            this->itemIOwn->pop_back();
        }

        void Entity::AddItem(std::shared_ptr<RG::NPC::Item> item){
            this->itemIOwn->push_back(item);
        }

        std::string Entity::GetName(){
            return this->name;
        }
    }
}
