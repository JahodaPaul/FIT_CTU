#include "View/Animation.hpp"
#include <iostream>

namespace RG {
    namespace View {
        Animation::Animation(const char *texture, int frameWidth, int frameHeigt, int frameCount, float timeStep)
                : m_frameCount(frameCount),
                  m_step(timeStep),
                  m_frameWidth(frameWidth),
                  m_frameHeight(frameHeigt),
                  m_rectSourceSprite(0, 0, frameWidth, frameHeigt),
                  m_sprite(m_texture, m_rectSourceSprite),
                  m_lastTime(0),
                  m_animating(false) {
            m_texture.loadFromFile(texture);
            m_sprite.setOrigin(frameWidth / 2, frameHeigt / 2);
            m_texture.setSmooth(true);
            m_sprite.setScale(1,1);
        }

        void Animation::update(float time) {
            if (!m_animating)
                return;
            float delta = time - m_lastTime;
            if (delta >= m_step) {
                m_rectSourceSprite.left += m_frameWidth * ((int) (delta / m_step) % m_frameCount);
                if (m_rectSourceSprite.left >= m_frameCount * m_frameWidth)
                    m_rectSourceSprite.left = 0;
                m_sprite.setTextureRect(m_rectSourceSprite);
                //TODO(vojta) add remainder
                m_lastTime = time;
            }
        }

        void Animation::goToFrame(unsigned int frame) {
            m_rectSourceSprite.left = m_frameWidth * (frame % m_frameCount);
            m_sprite.setTextureRect(m_rectSourceSprite);
        }

        void Animation::startAnimation() {
            m_animating = true;
        }

        void Animation::stopAnimation() {
            m_animating = false;
        }

        void Animation::setPosition(sf::Vector2f pos) {
            m_sprite.setPosition(pos);
        }

        sf::Vector2f Animation::getPosition() {
            return m_sprite.getPosition();
        }

        void Animation::setRotation(float angle) {
            m_sprite.setRotation(angle);
        }

        float Animation::getRotation() {
            return m_sprite.getRotation();
        }

        void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(m_sprite);
        }
    }
}
