#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <cstdio>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../../imgui-sfml/imgui-SFML.h"
#include "../../imgui/imgui.h"

namespace RG{

    class IOManager{

        public:

            IOManager(std::string dir = "/home/wiedzmin/FIT_CVUT/SP1/RG/test/Util/IOManager/keys", std::string fileName = "mapping.txt");
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
            const char * m_Keys[101] = {
                    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                    "U", "V", "W", "X", "Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8",
                    "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt",
                    "RSystem", "Menu", "LBracket", "RBracket", "SemiColon", "Comma", "Period", "Quote", "Slash",
                    "BackSlash", "Tilde", "Equal", "Dash", "Space", "Return", "BackSpace", "Tab", "PageUp", "PageDown",
                    "End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", "Divide", "Left", "Right", "Up",
                    "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7",
                    "Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                    "F13", "F14", "F15", "Pause"
            };
            std::fstream m_Stream;
            std::string m_StorageDir;
            std::string m_File;

    };

}