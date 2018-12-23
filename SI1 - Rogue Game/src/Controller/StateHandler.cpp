#include "Controller/StateHandler.hpp"
#include "Controller/GameController.hpp"

namespace RG { namespace Controller {
    StateHandler::StateHandler() {
        mainLog.Info("StateHandler Constructor");
    }
    void StateHandler::Update( float timeStep ) { }
    void StateHandler::GoToMainMenu( GameController * gameController ) {
        mainLog.Info("StateHandler GoToMainMenu");
    }
    void StateHandler::GoToGame( GameController * gameController ) {
        mainLog.Info("StateHandler StartGame");
        gameController->setActiveGameState(STATES::RUNNING);
    }
    void StateHandler::Quit( GameController * gameController ) {
        mainLog.Info("StateHandler StopGame");
    }
} }
