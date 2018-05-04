//
// Created by pjahoda on 1.5.18.
//

#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include "RoomHistory.hpp"
#include "SFML/Graphics.hpp"

namespace RG{
    namespace View{
        class Room:RoomHistory{
        public:
            Room();
            ~Room();
            void DrawRoom(int level, int id, sf::RenderTarget &target);
            void DrawDoor(sf::RenderTarget &target, bool top, bool right, bool down, bool left);
            void SetSpriteScale(float,float);
        protected:
        private:
            int currentId;
            void AssignBackground(int level, int id);
            void SetDoorPosition();
            sf::Texture room_texure;
            sf::Sprite background;
            float windowX;
            float windowY;

            sf::Texture door_up_texture;
            sf::Sprite door_up;

            sf::Texture door_right_texture;
            sf::Sprite door_right;

            sf::Texture door_down_texture;
            sf::Sprite door_down;

            sf::Texture door_left_texture;
            sf::Sprite door_left;

        };
    }
}

#endif //GAME_ROOM_H
