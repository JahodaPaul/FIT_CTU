#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>

#include "View/Animation.hpp"
#include "View/Entity.hpp"
#include "Util/Observer.hpp"
#include "Util/Subject.hpp"
#include "Util/Event.hpp"
#include "Model/Entity.hpp"

namespace RG{
    namespace View {
        class View;
        class GameScene;
        class Player : public Entity {
        public:
            Player(GameScene *gameScene, sol::state & luaState);
            virtual ~Player();

            void SetPlayerSpeedY(float y);

            void SetPlayerSpeedX(float x);

            float GetPlayerSpeedY();

            float GetPlayerSpeedX();
        private:
            float relativeMoveX;
            float relativeMoveY;
        };
    }
}
