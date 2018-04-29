#include "View/GameScene.hpp"
#include <View/Animation.hpp>

namespace RG {
    GameScene::GameScene() {
    }
    GameScene::~GameScene() {
    }
    void GameScene::Update( View * view ) {

    }
    void GameScene::Render( View * view ) {
        std::shared_ptr<Animation> animation = view->GetPlayer()->UpdateAndGetPlayer(0.0f,0.0f);
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

            bool moved = false;
            if(event.key.code == sf::Keyboard::Right){
                if (event.type == sf::Event::KeyPressed) {
                    std::shared_ptr<Animation> animation = view->GetPlayer()->UpdateAndGetPlayer(3.0f, 0.0f);
                    moved = true;
                }
            }
            if(event.key.code == sf::Keyboard::Left){
                if (event.type == sf::Event::KeyPressed) {
                    std::shared_ptr<Animation> animation = view->GetPlayer()->UpdateAndGetPlayer(-3.0f, 0.0f);
                    moved = true;
                }
            }
            if(event.key.code == sf::Keyboard::Up){
                if (event.type == sf::Event::KeyPressed) {
                    std::shared_ptr<Animation> animation = view->GetPlayer()->UpdateAndGetPlayer(0.0f, -3.0f);
                    moved = true;
                }
            }
            if(event.key.code == sf::Keyboard::Down){
                if (event.type == sf::Event::KeyPressed) {
                    std::shared_ptr<Animation> animation = view->GetPlayer()->UpdateAndGetPlayer(0.0f, 3.0f);
                    moved = true;
                }
            }
            if(!moved){
                std::shared_ptr<Animation> animation = view->GetPlayer()->UpdateAndGetPlayer(0.0f,0.0f);
            }
        }
    }
}
