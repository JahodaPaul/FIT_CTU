#include "View/MenuScene.hpp"

namespace RG {
    MenuScene::MenuScene() {
        std::cout <<"menu scene constructor" << std::endl;
    }
    MenuScene::~MenuScene() {}
    void MenuScene::Update( View * view ) {}
    void MenuScene::Render( View * view ) {
        view->getWindow()->clear({255,0,0,255});
        view->getWindow()->display();
    }
    void MenuScene::ManageInput( View * view ) {
        std::shared_ptr<sf::RenderWindow> window = view->getWindow();
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                view->getGameController()->Quit();
                return;
            }
        }
    }
}
