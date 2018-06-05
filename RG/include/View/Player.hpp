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

namespace RG{ namespace View {
    class View;
    class GameScene;
    /**
     * \class Player
     * \brief Graphical representation of player in view
     *
     * Player is using data from 'characters.lua' to choose correct texture, sounds etc.
     * 
     */
    class Player : public Entity {
        public:
            /**
             * \brief Constructor is mostly delegated to View::Entity
             *
             * @param gameScene pointer to GameScene
             * @param luaState pointer to lua state
             * 
             */
            Player(GameScene *gameScene, sol::state & luaState, float width, float height);

            /**
             * \brief Destructor
             */
            virtual ~Player();

            /**
             * \brief set player speed ( this does only store value )
             *
             * @param y size of move along y axis
             *
             */
            void SetPlayerSpeedY(float y);

            /**
             * \brief set player speed ( this does only store value )
             *
             * @param x size of move along x axis
             *
             */
            void SetPlayerSpeedX(float x);

            /**
             * \brief get Y compound of player speed ( this was store using SetPlayerSpeedY )
             */
            float GetPlayerSpeedY();

            /**
             * \brief get X compound of player speed ( this was store using SetPlayerSpeedX )
             */
            float GetPlayerSpeedX();
        private:
            float relativeMoveX;
            float relativeMoveY;
    };
} }
