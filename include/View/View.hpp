#pragma once

#include <memory>
#include <map>
#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Util/Vect2.hpp"
#include "View/MenuScene.hpp"
#include "View/Console.hpp"
#include "Controller/GameController.hpp"

namespace RG {
    class GameController;
    class Scene;
    enum SCENE { MENU_SCENE };
    class View {
        public:
            View( GameController * controller, Vect2f windowSize = { 900,600 }, const char * windowTitle = "game" );
            ~View();
            void Update();
            void Render();
            void ManageInput();
            std::shared_ptr<sf::RenderWindow> getWindow();
            GameController * getGameController();
            sf::Clock & getClock();

        private:
            void ShowDebugWindow();
            std::shared_ptr<sf::RenderWindow> m_window;
            sf::View m_view;
            SCENE m_activeScene;
            GameController * m_gameControllet;
            std::map<SCENE, std::shared_ptr<Scene> > m_mapOfGameScenes;
            sf::Clock m_clock;

            //TODO(vojta)
            std::map<std::string, std::function<void(void)>> m_api;
            bool m_ImguiDemo;
            Console m_console;
    };
}
