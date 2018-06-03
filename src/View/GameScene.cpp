#include "View/GameScene.hpp"

namespace RG {
    namespace View {
        GameScene::GameScene(View *view) :
            Scene( view )
            ,m_viewSize{ view->getWindow()->getView().getSize() }
            ,m_windowSize{ view->getWindow()->getSize() }
            ,m_npcLog( &view->getGameController()->getNPCWorldCycle().getMarket().getMatchingEngine() )
            ,m_gui( view )
            ,m_model{ &view->getGameController()->getModel() }
        {
            player = std::make_shared<Player>(
                    this
                    ,view->getLuaState()
                    ,view->getGameController()->getModel().GetPlayer().GetWidth()
                    ,view->getGameController()->getModel().GetPlayer().GetHeight()
                    );
            player->SubscribeTo( &view->getGameController()->getModel() );
            room = std::make_shared<RG::View::Room>(this, view->getLuaState(), &view->getGameController()->getModel() );
            player->SubscribeTo( &view->getGameController()->getModel().GetPlayer() );
            player->SubscribeTo( &view->getGameController()->getModel().GetCurrentFloor() );
            player->SubscribeTo( this );
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
            if ( m_windowSize.x > 600 )
                m_npcLog.Draw("Trading", NULL, m_windowSize.x - 410, 20);
            view->getWindow()->draw( *room );
            view->getWindow()->draw( *player );
            m_gui.Draw();
        }

        void GameScene::ManageInput(View *view) {

            std::shared_ptr<sf::RenderWindow> window = view->getWindow();
            sf::Event event;

            float speed = 30;

            while (window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);

                if(event.key.code == view->m_IOManager.GetMapped(sf::Keyboard::Escape)){
                    if (event.type == sf::Event::KeyPressed) {
                        m_gui.ToggleMenu();
                    }
                }

                if(event.key.code == view->m_IOManager.GetMapped(sf::Keyboard::Right)){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedX(speed);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedX(speed * -1);
                    }
                }
                if(event.key.code == view->m_IOManager.GetMapped(sf::Keyboard::Left)){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedX(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedX(speed);
                    }
                }
                if(event.key.code == view->m_IOManager.GetMapped(sf::Keyboard::Up)){
                    if (event.type == sf::Event::KeyPressed) {
                        player->SetPlayerSpeedY(speed * -1);
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        player->SetPlayerSpeedY(speed);
                    }
                }
                if(event.key.code == view->m_IOManager.GetMapped(sf::Keyboard::Down)){
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
                    m_viewSize = view->getWindow()->getView().getSize();
                    m_windowSize = view->getWindow()->getSize();
                    Notify( this, Util::Event::WINDOW_RESIZE );
                }

                if(event.key.code == view->m_IOManager.GetMapped(sf::Keyboard::Space)){
                    if (event.type == sf::Event::KeyPressed) {
                        view->getGameController()->getModel().Shoot();
                    }
                }
            }
        }

        const sf::Vector2f & GameScene::getViewSize() const {
            return m_viewSize;
        }
        const sf::Vector2u & GameScene::getWindowSize() const {
            return m_windowSize;
        }

        std::shared_ptr<Player> GameScene::getPlayer() {
            return player;
        }

        RG::Model::Model * GameScene::getModel() {
            return m_model;
        }
    }
}
