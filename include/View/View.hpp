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
#include "View/Player.hpp"
#include "View/Room.hpp"

#include "Controller/GameController.hpp"
#include "View/IOManager.hpp"


namespace RG {
        class GameController;
    namespace View {
        class Scene;

        enum SCENE {
            MENU_SCENE, GAME_SCENE
        };

        class View {
        public:
            View(GameController *controller, std::pair<int,int> windowSize = {900, 600}, const char *windowTitle = "game");

            ~View();

            void Update();

            void Render();

            void ManageInput();

            std::shared_ptr<sf::RenderWindow> getWindow();

            GameController *getGameController() const;

            const sf::Clock &getClock() const;

            void setActiveView(SCENE scene);

            std::shared_ptr<RG::View::Player> GetPlayer();

            void SetPlayer();

            void UpdatePlayer(float, float);

            void DrawPlayer();

            void DrawRoom();

            const sf::View GetView();

            IOManager m_IOManager;
        private:
            std::shared_ptr<sf::RenderWindow> m_window;
            SCENE m_activeScene;
            GameController *m_gameControllet;
            std::map<SCENE, std::shared_ptr<Scene> > m_mapOfGameScenes;
            sf::Clock m_clock;


            bool m_ImguiDemo;
            Console m_console;

            std::shared_ptr<RG::View::Player> player;
            std::shared_ptr<RG::View::Room> room;
        };
    }
}
