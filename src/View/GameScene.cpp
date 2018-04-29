#include "View/GameScene.hpp"

namespace RG {
    GameScene::GameScene() {
    }
    GameScene::~GameScene() {
    }
    void GameScene::Update( View * view ) {
        bool moved = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            std::shared_ptr<Animation> animation = view->getGameController()->UpdateAndGetPlayer(0.1f,0.0f);
            moved = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            std::shared_ptr<Animation> animation = view->getGameController()->UpdateAndGetPlayer(-0.1f,0.0f);
            moved = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            std::shared_ptr<Animation> animation = view->getGameController()->UpdateAndGetPlayer(0.0f,-0.1f);
            moved = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            std::shared_ptr<Animation> animation = view->getGameController()->UpdateAndGetPlayer(0.0f,0.1f);
            moved = true;
        }
        if(!moved){
            std::shared_ptr<Animation> animation = view->getGameController()->UpdateAndGetPlayer(0.0f,0.0f);
        }

    }
    void GameScene::Render( View * view ) {
        std::shared_ptr<Animation> animation = view->getGameController()->UpdateAndGetPlayer(0.0f,0.0f);
        animation->draw(*view->getWindow(),sf::RenderStates());
    }
    void GameScene::ManageInput( View * view ) {

        std::shared_ptr<sf::RenderWindow> window = view->getWindow();
        sf::Event event;
        while (window->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window->close();
                view->getGameController()->Quit();
                return;
            }
        }
    }
}
