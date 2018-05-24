#include "View/GameScene.hpp"

namespace RG {
    namespace View {
        GameScene::GameScene(View *view) :
            Scene( view )
            ,m_windowSize{ view->getWindow()->getView().getSize() }
            ,m_firstFrame{ true }
        {
            player = std::make_shared<Player>(this, view->getLuaState());
            room = std::make_shared<RG::View::Room>(this, view->getLuaState(), &view->getGameController()->getModel() );
            view->getGameController()->getModel().GetPlayer().AddObserver( player.get() );
            view->getGameController()->getModel().GetCurrentFloor().AddObserver( player.get() );
            room->ChangeRoom(&view->getGameController()->getModel().GetCurrentFloor());
            Notify( this, Util::Event::WINDOW_RESIZE );
        }

        GameScene::~GameScene() {
        }

        void GameScene::Update(View *view, float timeElapsed) {
            if ( ! player->Alive() ) {
                view->setActiveView( SCENE::GAME_OVER_SCENE );
                view->getSoundManager().PlayMusic("duckers");
            }

            view->getGameController()->RunNPCWorld();
            view->getGameController()->MoveModel(player->GetPlayerSpeedX(),player->GetPlayerSpeedY());
            player->Update(view, timeElapsed);
            room->Update(view, timeElapsed);
        }

        void GameScene::Render(View *view) {
            view->getWindow()->draw( *room );
            view->getWindow()->draw( *player );
        }

        void GameScene::ManageInput(View *view) {

            std::shared_ptr<sf::RenderWindow> window = view->getWindow();
            sf::Event event;

            float speed = 30;

            while (window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);

                if(event.key.code == sf::Keyboard::Right){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedX(speed);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedX(speed * -1);
                    }
                }
                if(event.key.code == sf::Keyboard::Left){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedX(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedX(speed);
                    }
                }
                if(event.key.code == sf::Keyboard::Up){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedY(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedY(speed);
                    }
                }
                if(event.key.code == sf::Keyboard::Down){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedY(speed);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedY(speed * -1);
                    }
                }

                if (event.type == sf::Event::Closed) {
                    window->close();
                    view->getGameController()->Quit();
                    return;
                }

                if (event.type == sf::Event::Resized) {
                    m_windowSize = view->getWindow()->getView().getSize();
                    Notify( this, Util::Event::WINDOW_RESIZE );
                }
            }
        }

        const sf::Vector2f & GameScene::getWindowSize() const {
            return m_windowSize;
        }
    }
}
