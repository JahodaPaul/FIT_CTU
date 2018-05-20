//
// Created by pjahoda on 1.5.18.
//
#include "View/Room.hpp"

namespace RG {
    namespace View {

        RG::View::Room::Room():room_bluestone("/usr/share/RG/assets/graphics/backgrounds/rooms/BlueStoneBG.png"),
                               room_blackstone("/usr/share/RG/assets/graphics/backgrounds/rooms/BlackStoneBG.png"),
                                room_cobblestone("/usr/share/RG/assets/graphics/backgrounds/rooms/CobbleStoneBG.png"),
                                room_soil("/usr/share/RG/assets/graphics/backgrounds/rooms/SoilBG.png"),
                                room_lava("/usr/share/RG/assets/graphics/backgrounds/rooms/LavaBG.png"){
            currentId = -1;
            this->door_up_texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-top.png");
            this->door_right_texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-right.png");
            this->door_down_texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-bottom.png");
            this->door_left_texture.loadFromFile("/usr/share/RG/assets/graphics/objects/doors/door-left.png");
            this->door_up.setTexture(door_up_texture);
            this->door_right.setTexture(door_right_texture);
            this->door_down.setTexture(door_down_texture);
            this->door_left.setTexture(door_left_texture);
//            this->door_up.setOrigin(this->door_up.getLocalBounds().width / 2, this->door_up.getLocalBounds().height / 2);
        }

        RG::View::Room::~Room() {

        }

        void RG::View::Room::AssignBackground(int level, int id) {
            std::string first;
            std::string second;
            if(level == 0){
                first = room_bluestone;
                second = room_blackstone;
            }
            else if(level == 1){
                first = room_blackstone;
                second = room_cobblestone;
            }
            else if(level == 2){
                first = room_cobblestone;
                second = room_soil;
            }
            else{
                first = room_soil;
                second = room_lava;
            }

            this->currentId = id;
            if(std::rand() % 2 == 0){
                this->roomHistory.insert(std::make_pair(std::to_string(id),first));
            }
            else{
                this->roomHistory.insert(std::make_pair(std::to_string(id),second));
            }
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

        void Room::SetDoorPosition(){
            door_up.setPosition((this->windowX/2)-(this->door_up.getLocalBounds().width* this->door_up.getScale().x/2),0);
            door_right.setPosition(this->windowX-(this->door_right.getLocalBounds().width * this->door_right.getScale().x),(this->windowY/2)-(this->door_right.getLocalBounds().height* this->door_right.getScale().y/2));
            door_down.setPosition((this->windowX/2)-(this->door_down.getLocalBounds().width* this->door_down.getScale().x/2),this->windowY-(this->door_down.getLocalBounds().height*this->door_down.getScale().y));
            door_left.setPosition(0,(this->windowY/2)-(this->door_left.getLocalBounds().height* this->door_left.getScale().y/2));
        }

        void Room::SetSpriteScale(float x, float y) {
            if (this->windowX != x || this->windowY != y) {
                this->windowX = x;
                this->windowY = y;
                this->SetDoorPosition();
                background.setScale(x / this->background.getLocalBounds().width, y / this->background.getLocalBounds().height);
                SetDoorScaleTopBot(x,y);
                SetDoorScaleLeftRight(x,y);
            }
        }

        void Room::SetDoorScaleTopBot(float x, float y){
            float scaleY = (float)(y / 7.5) / this->door_up.getLocalBounds().height;
            this->door_up.setScale(scaleY,scaleY);
            this->door_down.setScale(scaleY,scaleY);
        }

        void Room::SetDoorScaleLeftRight(float x, float y){
            float scaleX = (x / 9) / this->door_up.getLocalBounds().width;
            this->door_right.setScale(scaleX,scaleX);
            this->door_left.setScale(scaleX,scaleX);
        }

        void Room::DrawDoor(sf::RenderTarget &target, bool top, bool right, bool down, bool left,float x, float y) {
            if(winDoorsX != x || winDoorsY != y){
                SetDoorScaleTopBot(x,y);
                SetDoorScaleLeftRight(x,y);
                SetDoorPosition();
                winDoorsX = x;
                winDoorsY = y;
            }

            if(top){
                target.draw(door_up);
            }
            if(right){
                target.draw(door_right);
            }
            if(down){
                target.draw(door_down);
            }
            if(left){
                target.draw(door_left);
            }
        }
    }
}
