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
        class Entity : public Util::Observer, public sf::Drawable {
        public:
            Entity(GameScene * gameScene, sol::state & luaState, std::string name, float sizeY = 20, float sizeX = 20);
            virtual ~Entity();

            void setCorrection( float correctionX, float correctionY );

            void Update(View * view, float timeElapsed);

            void draw(sf::RenderTarget &target, sf::RenderStates states) const;

            void SetScale(float x, float y);

            virtual void onNotify(Util::Subject * subject, Util::Event event) override;

            bool Alive() const;

        protected:
            void SetPosition(float x, float y);

            float windowX;
            float windowY;
            float correctionX;
            float correctionY;

            float x;
            float y;

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
