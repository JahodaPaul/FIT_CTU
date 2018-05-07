#pragma once

#include <memory>
#include <map>
#include <vector>

#include "Controller/MenuStateHandler.hpp"
#include "Controller/GameStateHandler.hpp"

#include "Model/Model.hpp"

#include "View/View.hpp"

#include "NPC/NPCWorldCycle.hpp"

#include "common.hpp"

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

            int GetRoomId();
            int GetFloorLevel();

            void RunNPCWorld();

            ///top right down left
            std::vector<bool> GetRoomDoors();
        private:
            std::shared_ptr<RG::View::View> m_view;
            std::map<int, std::shared_ptr<GameStateHandler> > m_mapOfGameStateHandlers;
            int m_GameState;
            std::shared_ptr<RG::Model::Model> m_model;
            std::shared_ptr<RG::NPC::NPCWorldCycle> m_NPCWorld;

            int m_howOftenRunNPCWorld;
    };
}
