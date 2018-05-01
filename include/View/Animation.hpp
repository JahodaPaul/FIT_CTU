#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

//TODO(vojta) add documnetation
//TODO(vojta) use ChacheManager for loading texture
namespace RG {
    class Animation : public sf::Drawable {
        public:
            Animation(const char * texture, int frameWidth, int frameHeigt, int frameCount, float timeStep );
            void update( float time );
            void goToFrame( unsigned int frame );
            void startAnimation();
            void stopAnimation();
            void setPosition( sf::Vector2f pos );
            sf::Vector2f getPosition();
            void setRotation( float angle );
            float getRotation();
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        private:
            sf::Texture m_texture;
            int m_frameCount;
            float m_step;
            int m_frameWidth;
            int m_frameHeight;
            sf::IntRect m_rectSourceSprite;
            sf::Sprite m_sprite;
            float m_lastTime;
            bool m_animating;
    };
}
