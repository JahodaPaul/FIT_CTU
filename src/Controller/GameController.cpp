#include "Controller/GameController.hpp"

namespace RG {
    GameController::GameController() : m_running( false ) {
        std::cout << "GameController Constructor" << std::endl;
        m_mapOfGameStateHandlers[STATES::MAIN_MENU] = std::shared_ptr<GameStateHandler>( new MenuStateHandler() );
        m_mapOfGameStateHandlers[STATES::RUNNING] = std::shared_ptr<GameStateHandler>( new GameStateHandler() );
        m_GameState = STATES::MAIN_MENU;
        m_view = std::make_shared<View>(this);
        m_game = NULL;
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
        m_game = std::make_shared<Game>();
        m_game->SetPlayer();
        m_game->GetPlayer()->GetAnimation()->goToFrame(0);
        m_game->GetPlayer()->GetAnimation()->startAnimation();
    }
    void GameController::setActiveGameState( STATES state ) {
        m_GameState = state;
    }

    std::shared_ptr<Animation> GameController::UpdateAndGetPlayer(float x,float y){
        if(x || y){
            m_game->GetPlayer()->UpdatePosition(x,y);
            m_game->GetPlayer()->Update(0.001f);
        }
        else{
            m_game->GetPlayer()->Update(0.0f);
        }
        return m_game->GetPlayer()->GetAnimation();
    }
}
