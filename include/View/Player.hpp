//
// Created by pjahoda on 29.4.18.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>
#include "View/Animation.hpp"
#include "Util/Observer.hpp"
#include "Util/Subject.hpp"
#include "Util/Event.hpp"
#include "Model/Entity.hpp"

namespace RG{
    namespace View {
        class View;
        class Player : public Util::Observer {
        public:
            Player();
            virtual ~Player();

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

            virtual void onNotify(const Util::Subject * subject, Util::Event event) override;

        protected:
        private:
            sf::RectangleShape player;
            sf::Texture playerTexture;
            float windowX;
            float windowY;

            float x;
            float y;

            bool m_moved;

            float relativeMoveX;
            float relativeMoveY;
            float time;
            std::shared_ptr<Animation> animation;
        };
    }
}


#endif //GAME_PLAYER_H
