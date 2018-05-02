//
// Created by pjahoda on 1.5.18.
//
#include "View/Room.hpp"


namespace RG {
    namespace View {

        RG::View::Room::Room() {
            currentId = -1;
        }

        RG::View::Room::~Room() {

        }

        void RG::View::Room::AssignBackground(int level, int id) {
            this->currentId = id;
            this->roomHistory.insert(std::make_pair(std::to_string(id),"../assets/graphics/backgrounds/rooms/BlackStoneBG.png")); //TODO do it almost random -> dependent on level
        }

        void RG::View::Room::DrawRoom(int level, int id, sf::RenderTarget &target) {
            if(id == this->currentId){
                target.draw(background);
                return;
            }
            if(this->roomHistory.find(std::to_string(id)) == this->roomHistory.end()){
                this->AssignBackground(level,id);
            }
            else{
                this->currentId = id;
            }

            auto it = this->roomHistory.find(std::to_string(id));
            room_texure.loadFromFile(it->second);
            background.setTexture(room_texure);
            target.draw(background);
        }

    }
}