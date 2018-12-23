#pragma once

#include <memory>
#include <iostream>

#include "Controller/GameController.hpp"
#include "Controller/StateHandler.hpp"
#include "common.hpp"

namespace RG { namespace Controller {
    class GameController;
    /**
     * \class GameStateHandler
     * \brief
     */
    class GameStateHandler : public StateHandler
    {
        public:
            GameStateHandler();
            virtual ~GameStateHandler(){}
            virtual void GoToMainMenu( GameController * gameController );
            virtual void GoToGame( GameController * gameController );
            virtual void Quit( GameController * gameController );
            virtual void Update( float timeStep );
    };
} }
