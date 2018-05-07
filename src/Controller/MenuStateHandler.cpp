#include "Controller/MenuStateHandler.hpp"

namespace RG {
    MenuStateHandler::MenuStateHandler() : GameStateHandler() {
        mainLog.Info("MenuState Constructor");
    }
    MenuStateHandler::~MenuStateHandler() { }
    void MenuStateHandler::Update( float timeStep ) { }
    void MenuStateHandler::GoToMainMenu( GameController * gameController ) {
        mainLog.Info("MenuState GoToMainMenu");
    }
    void MenuStateHandler::GoToGame( GameController * gameController ) {
        mainLog.Info("MenuState StartGame");
        gameController->setActiveGameState(STATES::RUNNING);
    }
    void MenuStateHandler::Quit( GameController * gameController ) {
        mainLog.Info("MenuState StopGame");
    }
}
