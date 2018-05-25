#pragma once

#include <memory>
#include <map>
#include <vector>

#include "Controller/MenuStateHandler.hpp"
#include "Controller/GameStateHandler.hpp"
#include "Controller/StateHandler.hpp"

#include "Model/Model.hpp"

#include "View/View.hpp"

#include "NPC/NPCWorldCycle.hpp"

#include "common.hpp"

namespace RG { namespace Controller {
    //! \enum STATES
    /*!
     *  \brief enumeration of all game states in Controller
     */
    enum STATES {
        //LOADING,
        MAIN_MENU, /**< menu state of game */
        RUNNING /**< play state of game */
        //GAME_OVER
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

            /// returns a floor-unique room id
            int GetRoomId();

            /// returns how deep under ground the player currently is
            int GetFloorLevel();

            void RunNPCWorld();

            ///top right down left
            std::vector<bool> GetRoomDoors();

            /// sends a message to the model to move the player in the physical world
            void MoveModel(float x, float y) const;

            /**
             * \function StepModel
             * \brief step time in the physical world
             * @param step how much time has elapsed since the last time the function was called
             */
            void StepModel(float step) const;
            
            Model::Model & getModel();
            NPC::NPCWorldCycle & getNPCWorldCycle();

        private:
            std::shared_ptr<RG::View::View> m_view;
            std::map<int, std::shared_ptr<StateHandler> > m_mapOfGameStateHandlers;
            int m_GameState;
            std::shared_ptr<RG::Model::Model> m_model;
            std::shared_ptr<RG::NPC::NPCWorldCycle> m_NPCWorld;

            int m_howOftenRunNPCWorld;
    };
} }
