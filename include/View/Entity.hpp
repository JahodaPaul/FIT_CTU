#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>

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
            Entity(GameScene * gameScene);
            virtual ~Entity();

            void Update(View * view, float timeElapsed);

            void draw(sf::RenderTarget &target, sf::RenderStates states) const;

            void SetScale(float x, float y);

            virtual void onNotify(const Util::Subject * subject, Util::Event event) override;

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
        };
    }
}
