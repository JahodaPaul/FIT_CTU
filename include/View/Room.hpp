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
        protected:
        private:
            int currentId;
            void AssignBackground(int level, int id);
            sf::Texture room_texure;
            sf::Sprite background;

        };
    }
}

#endif //GAME_ROOM_H
