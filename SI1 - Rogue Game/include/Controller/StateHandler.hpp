#pragma once

#include <memory>
#include <iostream>

#include "common.hpp"

namespace RG { namespace Controller {
    class GameController;
    /**
     * \class GameStateHandler
     * \brief
     */
    class StateHandler
    {
        public:
            StateHandler();
            virtual ~StateHandler(){}
            virtual void GoToMainMenu( GameController * gameController );
            virtual void GoToGame( GameController * gameController );
            virtual void Quit( GameController * gameController );
            virtual void Update( float timeStep );
    };
} }
