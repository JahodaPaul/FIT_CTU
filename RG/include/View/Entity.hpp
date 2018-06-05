#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>
#include <string>
#include <sol.hpp>

#include "View/Animation.hpp"
#include "Util/Observer.hpp"
#include "Util/Subject.hpp"
#include "Util/Event.hpp"
#include "Model/Entity.hpp"
#include "Model/Floor.hpp"

namespace RG{
    namespace View {
        class View;
        class GameScene;
        /**
         * \class Entity
         * \brief Graphical representation of Model::Entity in view
         *
         * Entity is using data from 'characters.lua' to choose correct texture, sounds etc.
         * 
         */
        class Entity : public Util::Observer, public sf::Drawable {
        public:
            /**
             * \brief Constructor
             *
             * @param gameScene pointer to GameScene
             * @param luaState pointer to lua state
             * @param name name of entity
             * 
             */
            Entity(GameScene * gameScene, sol::state & luaState, std::string name, float sizeY = 7, float sizeX = 7);

            /**
             * \brief Destructor
             */
            virtual ~Entity();

            /**
             *
             * Entity is getting absolute position from model, this position needs to be corrected with abs position of room in whitch this entity is.
             *
             * @param correctionX correction for x axis
             * @param correctionY correction for y axis
             * 
             */
            void setCorrection( float correctionX, float correctionY );

            /*!
             * \brief Updates Entity
             *
             * @param view pointer to View
             * @param timeElapsed time elapsed since last update
             */
            void Update(View * view, float timeElapsed);

            /*!
             * \brief Draws Entity
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;

            /*!
             * \brief Set new scaling of Entity
             *
             * @param x new scale of x axis
             * @param y new scale of y axis
             *
             */
            void SetScale(float x, float y);

            /*!
             * This methos is used to recieve nitifikations
             */
            virtual void onNotify(Util::Subject * subject, Util::Event event) override;

            /*!
             * \brief Test if entity is Alive
             *
             * This data is taken from model.
             *
             */
            bool Alive() const;

            void SetPosition(float x, float y);
        protected:

            float windowX;
            float windowY;
            float correctionX;
            float correctionY;

            float x;
            float y;

            int m_roomSizeX;
            int m_roomSizeY;

            bool m_moved;

            float time;
            std::shared_ptr<Animation> animation;
            float m_rotationCorrection;
            float sizeX;
            float sizeY;

            bool m_alive;
            sol::state * m_lua;
            std::string m_name;
        };
    }
}
