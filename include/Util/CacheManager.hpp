#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/**
 * \brief
 * Cache manager class provides the service of compact storing and caching of the SFML objects used in the game.
 */

namespace RG {

    ///Exception for the case of non existing storage folder
    class StorageException {
        public:
            StorageException(std::string folder): m_Folder(folder) {}
            std::string what() const throw() {
                return "Folder "+m_Folder+" doesn't exists.";
            }
        private:
            std::string m_Folder;
    };

    class CacheManager {

        public:

            /** Cache manager class constructor. */
            CacheManager(std::string folder = "cache");

            /** Texture manager class destructor. */
            ~CacheManager();

            /** Method for retrieving specified texture from CacheManager object. */
            std::pair <std::string, std::shared_ptr<sf::Texture>> getTexture(std::string textureName);

            /** Method for retrieving specified font from CacheManager object. */
            std::pair <std::string, std::shared_ptr<sf::Font>> getFont(std::string fontName);

            /** Method for deleting specified texture from CacheManager object. */
            bool deleteTexture(std::string textureName);

            /** Method for deleting specified font from CacheManager object. */
            bool deleteFont(std::string fontName);

            /** Method for setting the cache data folder.
             * The instance of RG::StorageException if thrown if the folder doesn't exist. */
            void SetStorageFolder(std::string folder);

            /** Method for testing file existence. */
            bool FileExists(std::string fileName);

        private:

            /** Method for creating error texture. */
            void CreateErrTexture();

            ///Member variable representing the cache data folder
            std::string m_StorageFolder;

            ///Member variable representing the storage for holding textures.
            std::map<std::string, std::pair<std::shared_ptr<sf::Texture>, int>> m_Textures;

            ///Member variable respresenting the storage for holding fonts
            std::map<std::string, std::pair<std::shared_ptr<sf::Font>, int>> m_Fonts;

    };

}