#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <cstdio>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace RG{

    class IOManager{

        public:

            IOManager(std::string dir = "keys", std::string fileName = "mapping.txt");
            ~IOManager();
            sf::Keyboard::Key GetMapped(sf::Keyboard::Key key);
            void MapKey(sf::Keyboard::Key toMap, sf::Keyboard::Key mapRes);
            void Serialize();
            void Deserialize();
            void Draw();

            void SetDefaultKeys();
            void SetStorageDir(std::string dir);
            void SetFile(std::string fileName);

            bool Open();
            bool Close();
            bool FileExists(std::string fileName);

        private:

            std::vector<sf::Keyboard::Key> m_KeyArr;
            std::fstream m_Stream;
            std::string m_StorageDir;
            std::string m_File;

    };

}