#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/**
 * \brief
 * Texture manager class provides the service of compact storing of the textures used in the game.
 */

namespace RG{
    class TextureManager{

        public:

            /** Texture manager class constructor. */
            TextureManager();

            /** Texture manager class destructor. */
            ~TextureManager();

            /** Method for retrieving specified texture from TextureManager object. */
            std::pair<std::string, std::shared_ptr<sf::Texture>> getTexture(std::string textureName);

            /** Method for deleting specified texture from TextureManager object. */
            bool deleteTexture(std::string textureName);

        private:

            ///Member variable representing the storage for holding textures.
            std::map<std::string, std::pair< std::shared_ptr<sf::Texture>, int>> textures;

    };
}