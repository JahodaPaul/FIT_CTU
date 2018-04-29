#include "View/GameScene.hpp"

namespace RG {
    GameScene::GameScene() {
    }
    GameScene::~GameScene() {
    }
    void GameScene::Update( View * view ) {

    }
    void GameScene::Render( View * view ) {
//        view->getWindow()->draw(view->getGameController()->UpdateAndGetPlayer(200.0f, 200.f));
        std::shared_ptr<Animation> animation = view->getGameController()->UpdateAndGetPlayer(200.0f,200.0f);
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
