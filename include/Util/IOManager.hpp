#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace RG{

    class IOManager{

        public:

            IOManager(std::string dir = "keys", std::string f = "mapping.txt");
            ~IOManager();
            sf::Keyboard::Key GetMapped(sf::Keyboard::Key key);
            void MapKey(sf::Keyboard::Key toMap, sf::Keyboard::Key mapRes);
            void Serialize();
            void Deserialize();
            void Draw();

            void SetStorageDir(std::string dir);
            void SetFile(std::string f);

        private:

            std::vector<sf::Keyboard::Key> keyArr;
            std::string storageDir;
            std::string file;

    };

}