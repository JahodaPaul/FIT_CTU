#include "Controller/GameController.hpp"

namespace RG {
    GameController::GameController() : m_running( false ) {
        std::cout << "GameController Constructor" << std::endl;
        m_mapOfGameStateHandlers[STATES::MAIN_MENU] = std::shared_ptr<GameStateHandler>( new MenuStateHandler() );
        m_mapOfGameStateHandlers[STATES::RUNNING] = std::shared_ptr<GameStateHandler>( new GameStateHandler() );
        m_GameState = STATES::MAIN_MENU;
        m_view = std::make_shared<View>(this);
    }
    GameController::~GameController() {}

    void GameController::Run() {
        m_running = true;
        std::cout << "Running" << std::endl;
        while ( m_running ) {
            if ( m_GameState == STATES::RUNNING ) {
                //TODO(vojta) update game model
            }
            m_view->ManageInput();
            m_view->Update();
            m_view->Render();
        }
    }
    int GameController::Quit() {
        std::cout <<"quit" << std::endl;
        m_running = false;
        return 0;
    }
    void GameController::setState( STATES s ) {
        m_GameState = s;
    }
    void GameController::Update( float timeStep ) { }
    void GameController::GoToMainMenu() {
        m_mapOfGameStateHandlers[m_GameState]->GoToMainMenu( this );
        m_view->setActiveView( SCENE::MENU_SCENE );
    }
    void GameController::GoToGame() {
        m_mapOfGameStateHandlers[m_GameState]->GoToGame( this );
        m_view->setActiveView( SCENE::GAME_SCENE );
    }
    void GameController::setActiveGameState( STATES state ) {
        m_GameState = state;
    }
}
