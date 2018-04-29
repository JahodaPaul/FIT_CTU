#pragma once

#include <memory>
#include <map>

#include <Controller/MenuStateHandler.hpp>
#include <Controller/GameStateHandler.hpp>

#include <Model/Game.h>

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
            void GoToGame();
            void Update( float timeStep );
            void Run();
            bool Running() { return m_running; }
            int Quit();
            void setState( STATES state );
            void setActiveGameState( STATES state );
            bool m_running;

            std::shared_ptr<Animation>  UpdateAndGetPlayer(float x,float y); //temporary function
        private:
            std::shared_ptr<View> m_view;
            std::map<int, std::shared_ptr<GameStateHandler> > m_mapOfGameStateHandlers;
            int m_GameState;
            std::shared_ptr<Game> m_game;
    };
}
