//
// Created by pjahoda on 29.4.18.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include "View/Animation.hpp"
#include <memory>
#include <math.h>

namespace RG{
    namespace View {
        class Player {
        public:
            Player();

            void SetPosition(float x, float y);

            void UpdatePosition(float x, float y);

            std::pair<float, float> GetPosition();

            sf::RectangleShape GetPlayerRectangleShape();

            std::shared_ptr<Animation> GetAnimation();

            void Update(float);

            void UpdatePlayer(float relativeMoveX, float relativeMoveY, float absoluteX, float absoluteY);

            void DrawPlayer(sf::RenderTarget &target);

            void SetPlayerScale(float x, float y);

        protected:
        private:
            sf::RectangleShape player;
            sf::Texture playerTexture;
            float windowX;
            float windowY;

            float x;
            float y;
            float time;
            std::shared_ptr<Animation> animation;

            float GetAngle(float moveX, float moveY);

            sf::Clock clock;
        };
    }
}


#endif //GAME_PLAYER_H
