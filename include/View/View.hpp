#pragma once

#include <memory>
#include <map>
#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include <sol.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "Util/Vect2.hpp"

#include "View/MenuScene.hpp"
#include "View/GameScene.hpp"
#include "View/GameOverScene.hpp"

#include "View/Console.hpp"

#include "View/IOManager.hpp"
#include "View/SoundManager.hpp"

#include "Controller/GameController.hpp"


namespace RG {
    namespace Controller { class GameController; }
    namespace View {
        class Scene;

        //! \enum SCENE
        /*!
         *  \brief enumeration of all game scenes
         */
        enum SCENE {
            MENU_SCENE, /**< main menu of game */
            GAME_SCENE, /**< state of playing the game */
            GAME_OVER_SCENE /**< end screen shown when you lose */
        };

        //! \class View
        /*!
         *  \brief
         *  This class is main class of RG::View namespace it manages all game scenes and switches between them.
         */
        class View {
        public:
            //! A constructor
            /*!
             * Constructor takes three parameters:
             * \param controller pointer to game controller
             * \param windowSize default size of game window
             * \param windowTitle title of game window
             */
            View(Controller::GameController *controller, std::pair<int,int> windowSize = {1280, 720}, const char *windowTitle = "game");

            //! destructor
            ~View();

            //! Method to update whole view, should be called periodically from controller.
            void Update();

            //! Render whole view, should be called periodically from controller.
            void Render();

            //! Maneg player input, should be called periodically from controller.
            void ManageInput();

            //! Get game window.
            /*!
             * \return shared pointer to game window - sf::RenderWindow
             */
            std::shared_ptr<sf::RenderWindow> getWindow();

            //! Get game controller
            /*!
             * \return pointer to game controller
             */
            Controller::GameController *getGameController() const;

            //! Change game scene
            /*!
             * \param scene type of scene
             */
            void setActiveView(SCENE scene);

            //! Get sfml view of window
            /*!
             * \return reference to sf::View
             */
            const sf::View & GetView();

            //! Get reference to soundManager
            /*!
             * \return reference to soundManager
             */
            SoundManager & getSoundManager();

            IOManager m_IOManager;

            sol::state & getLuaState();
        private:
            std::shared_ptr<sf::RenderWindow> m_window;
            SCENE m_activeScene;
            Controller::GameController *m_gameControllet;
            std::map<SCENE, std::shared_ptr<Scene> > m_mapOfGameScenes;
            sf::Clock m_clock;

            SoundManager m_soundManager;

            bool m_ImguiDemo;
            Console m_console;
            sf::Time m_timeElapsed;

            sol::state m_lua;
        };
    }
}
