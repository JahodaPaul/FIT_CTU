#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace RG { namespace View {

    //! \class CacheManager
    /*!
     * \brief
     * Cache manager class provides the service of compact storing and caching of the SFML objects used in the game.
     */
    class CacheManager {

        public:
            /// Exception for the case of non-existing storage folder.
            class StorageException {
                public:
                    StorageException(std::string folder): m_Folder(folder) {}
                    std::string what() const throw() {
                        return "Folder "+m_Folder+" doesn't exists.";
                    }
                private:
                    std::string m_Folder;
            };


            //! Cache manager class constructor.
            /*!
             * Method may take one parameter:
             * @param folder Cache data storage folder.
             */
            CacheManager(std::string folder = "cache");

            /// Texture manager class destructor.
            ~CacheManager();

            //! Method for retrieving specified texture from CacheManager object.
            /*!
             * Method takes one parameter:
             * @param textureName Texture identifier.
             * @return Structure containing the texture identifier and shared pointer to the texture.
             */
            std::pair <std::string, std::shared_ptr<sf::Texture>> getTexture(std::string textureName);

            //! Method for retrieving specified font from CacheManager object.
            /*!
             * Method takes one parameter:
             * @param fontName Font identifier.
             * @return Structure containing the font identifier and shared pointer to the font.
             */
            std::pair <std::string, std::shared_ptr<sf::Font>> getFont(std::string fontName);

            //! Method for deleting specified texture from CacheManager object.
            /*!
             * Method takes one parameter:
             * @param textureName Texture identifier.
             * @return True if the texture was deleted. False if the texture doesn't exist.
             */
            bool deleteTexture(std::string textureName);

            //! Method for deleting specified font from CacheManager object.
            /*!
             * Method takes one parameter:
             * @param fontName Font identifier.
             * @return True if the fond was deleted. False if the font doesn't exist.
             */
            bool deleteFont(std::string fontName);

            //! Method for setting the cache data folder.
            //! The instance of RG::StorageException is thrown if the folder doesn't exist.
            /*!
             * Method takes one parameter:
             * @param folder Cache storage folder.
             */
            void SetStorageFolder(std::string folder);

            //! Method for testing file existence.
            /*!
             * Method takes one parameter:
             * @param fileName Name of the file to test.
             * @return True if file exists. False if don't.
             */
            bool FileExists(std::string fileName);

        private:

            /// Method for creating error texture.
            void CreateErrTexture();

            /// Member variable representing the cache data folder.
            std::string m_StorageFolder;

            /// Member variable representing the storage for holding textures.
            std::map<std::string, std::pair<std::shared_ptr<sf::Texture>, int>> m_Textures;

            /// Member variable respresenting the storage for holding fonts.
            std::map<std::string, std::pair<std::shared_ptr<sf::Font>, int>> m_Fonts;

    };
} }
