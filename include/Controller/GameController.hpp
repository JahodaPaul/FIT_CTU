#pragma once

#include <memory>
#include <map>

#include <Controller/GameStateHandler.hpp>
#include <Controller/MenuStateHandler.hpp>

#include <View/View.hpp>

namespace RG {
    enum STATES {
        LOADING,
        MAIN_MENU,
        RUNNING,
        GAME_OVER
    };
    /**
     * \class GameController
     * \brief This is class is managing game states and act as controler in MVC model.
     */
    class GameController
    {
        public:
            GameController();
            ~GameController();
            void GoToMainMenu();
            void StartGame();
            void Update( float timeStep );
            void Run();
            bool Running() { return m_running; }
            void Quit();
            void setState( STATES state );
            bool m_running;
        private:
            std::shared_ptr<View> m_view;
            std::map<int, std::shared_ptr<GameStateHandler> > m_mapOfGameStateHandlers;
            int m_GameState;
    };
}
