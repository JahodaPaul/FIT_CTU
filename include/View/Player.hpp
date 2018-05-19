//
// Created by pjahoda on 29.4.18.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>
#include "View/Animation.hpp"

namespace RG{
    namespace View {
        class View;
        class Player {
        public:
            Player();

            void SetPosition(float x, float y);

            void UpdatePosition(float x, float y);

            std::pair<float, float> GetPosition();

            sf::RectangleShape GetPlayerRectangleShape();

            std::shared_ptr<Animation> GetAnimation();

            void UpdatePlayer(View * view, float timeElapsed); //float relativeMoveX, float relativeMoveY,

            void DrawPlayer(sf::RenderTarget &target);

            void SetPlayerScale(float x, float y);

            void SetPlayerSpeedY(float y);

            void SetPlayerSpeedX(float x);

            float GetPlayerSpeedY();

            float GetPlayerSpeedX();

        protected:
        private:
            sf::RectangleShape player;
            sf::Texture playerTexture;
            float windowX;
            float windowY;

            float x;
            float y;

            float relativeMoveX;
            float relativeMoveY;
            float time;
            std::shared_ptr<Animation> animation;
        };
    }
}


#endif //GAME_PLAYER_H
