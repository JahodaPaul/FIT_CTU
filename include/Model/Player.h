//
// Created by pjahoda on 29.4.18.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include <View/Animation.hpp>
#include <memory>

namespace RG{
    class Player{
    public:
        Player();
        void SetPosition(float x,float y);
        std::pair<float,float> GetPosition();
        sf::RectangleShape GetPlayerRectangleShape();
        std::shared_ptr<Animation> GetAnimation();
        void Update();
    protected:
    private:
        sf::RectangleShape player;
        sf::Texture playerTexture;
        float x;
        float y;
        std::shared_ptr<Animation> animation;
    };

}


#endif //GAME_PLAYER_H
