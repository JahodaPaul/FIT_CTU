//
// Created by pjahoda on 29.4.18.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>

namespace RG{
    class Player{
    public:
        Player();
        void SetPosition(float x,float y);
        std::pair<float,float> GetPosition();
        sf::RectangleShape GetPlayerRectangleShape();
    protected:
    private:
        sf::RectangleShape player;
        float x;
        float y;
    };

}


#endif //GAME_PLAYER_H
