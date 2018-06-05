#pragma once

#include "Controller/GameController.hpp"
#include "Controller/StateHandler.hpp"
#include "common.hpp"

namespace RG { namespace Controller {
    class GameController;
    /**
     * \class MenuStateHandler
     * \brief
     */
    class MenuStateHandler : public StateHandler
    {
        public:
            MenuStateHandler();
            virtual ~MenuStateHandler();
            virtual void Update( float timeStep );
            virtual void GoToMainMenu( GameController * gameController );
            virtual void GoToGame( GameController * gameController );
            virtual void Quit( GameController * gameController );
    };
} }
