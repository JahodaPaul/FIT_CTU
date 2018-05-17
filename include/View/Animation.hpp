#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"


//TODO(vojta) use ChacheManager for loading texture
namespace RG {
    namespace View {
        //! \class Animation
        /*!
         *  \brief Animation class
         *  This class is used for animating sprites.
         */
        class Animation : public sf::Drawable {
        public:
            //! A constructor
            /*!
             * Constructor takes five parameters:
             * \param texture path to picture with frames
             * \param frameWidth width of one frame
             * \param frameHeigt height of one frame
             * \param frameCount number of frames
             * \param timeStep time between frames
             */
            Animation(const char *texture, int frameWidth, int frameHeigt, int frameCount, float timeStep);

            //! Method to update the animation, must be called every frame to work correctly.
            /*!
             * \param timeElapsed time elapsed from previous frame
             */
            void update(float timeElapsed);

            //! Force animation to specific frame
            /*!
             * \param frameNumber number of frame starting from 0
             */
            void goToFrame(unsigned int frameNumber);

            //! Stop animation
            void stopAnimation();

            //! Start animation ( only makes sence after stopAnimation )
            void startAnimation();

            //! Set position of sprite
            /*!
             * \param pos new position of sprite
             */
            void setPosition(sf::Vector2f pos);

            //! Get position of sprite.
            /*!
             * \return position of sprite 
             */
            sf::Vector2f getPosition();

            //! Set rotation of sprite.
            /*!
             * \param angle new angle in degrees
             */
            void setRotation(float angle);

            //! Get rotation of sprite.
            /*!
             * \return rotation in degrees 
             */
            float getRotation();

            //! Draw sprite - can be called as RenderWindow.draw( animation ) 
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;

            //! Set scale of sprite
            /*!
             * \param factorX
             * \param factorY
             */
            void setScale(float factorX, float factorY);

            //! Get scale of sprite
            /*!
             * \return scale of sprite as sf::Vector2f
             */
            const sf::Vector2f& getScale() const;

            //! Get size of one frame
            /*!
             * \return size as sf::Vector2u 
             */
            sf::Vector2u getSize() const;

        private:
            sf::Texture m_texture;
            int m_frameCount;
            float m_step;
            int m_frameWidth;
            int m_frameHeight;
            sf::IntRect m_rectSourceSprite;
            sf::Sprite m_sprite;
            float m_timeLeft;
            bool m_animating;
        };
    }
}
