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
#include "View/GameScene.hpp"
#include "View/Console.hpp"

#include "View/IOManager.hpp"
#include "View/SoundManager.hpp"

#include "Controller/GameController.hpp"


namespace RG {
        namespace Controller { class GameController; }
    namespace View {
        class Scene;

        enum SCENE {
            MENU_SCENE, GAME_SCENE
        };

        class View {
        public:
            View(Controller::GameController *controller, std::pair<int,int> windowSize = {900, 600}, const char *windowTitle = "game");

            ~View();

            void Update();

            void Render();

            void ManageInput();

            std::shared_ptr<sf::RenderWindow> getWindow();

            Controller::GameController *getGameController() const;

            const sf::Clock &getClock() const;

            void setActiveView(SCENE scene);

            const sf::View GetView();

            SoundManager & getSoundManager();

            IOManager m_IOManager;
        private:
            std::shared_ptr<sf::RenderWindow> m_window;
            SCENE m_activeScene;
            Controller::GameController *m_gameControllet;
            std::map<SCENE, std::shared_ptr<Scene> > m_mapOfGameScenes;
            sf::Clock m_clock;

            SoundManager m_soundManager;


            bool m_ImguiDemo;
            Console m_console;
        };
    }
}
