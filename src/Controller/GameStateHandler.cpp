#include "Controller/GameStateHandler.hpp"

namespace RG { namespace Controller {
    GameStateHandler::GameStateHandler() : StateHandler() {
        mainLog.Info("gameState Constructor");
    }
    void GameStateHandler::Update( float timeStep ) { }
    void GameStateHandler::GoToMainMenu( GameController * gameController ) {
        mainLog.Info("GameStateHandler GoToMainMenu");
    }
    void GameStateHandler::GoToGame( GameController * gameController ) {
        mainLog.Info("GameStateHandler StartGame");
        gameController->setActiveGameState(STATES::RUNNING);
    }
    void GameStateHandler::Quit( GameController * gameController ) {
        mainLog.Info("GameStateHandler StopGame");
    }
} }
