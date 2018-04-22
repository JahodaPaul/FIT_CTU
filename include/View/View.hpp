#pragma once

#include <memory>
#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Util/Vect2.hpp"
#include "View/MenuScene.hpp"
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

        private:
            std::shared_ptr<sf::RenderWindow> m_window;
            sf::View m_view;
            SCENE m_activeScene;
            GameController * m_gameControllet;
            std::map<SCENE, std::shared_ptr<Scene> > m_mapOfGameScenes;
    };
}
