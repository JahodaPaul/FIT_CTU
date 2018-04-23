#include "View/MenuScene.hpp"

namespace RG {
    MenuScene::MenuScene() {
        std::cout <<"menu scene constructor" << std::endl;
    }
    MenuScene::~MenuScene() {}
    void MenuScene::Update( View * view ) {}
    void MenuScene::Render( View * view ) {
        ImGui::SFML::Update(*view->getWindow(), view->getClock().restart());

        ImGui::SetNextWindowBgAlpha(0);
        ImGui::GetStyle().WindowBorderSize = 0;
        ImGui::Begin("", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize );
        //ImGui::PushItemHeight( 300 );
        if (ImGui::Button("New Game", ImVec2(100,50))) {
        }
        if (ImGui::Button("Higscores", ImVec2(100,50))) {
        }
        if (ImGui::Button("Exit", ImVec2(100,50)))
            view->getGameController()->Quit();
        ImGui::End();

        ImGui::ShowDemoWindow();

        view->getWindow()->clear({255,0,0,255});

        ImGui::SFML::Render(*view->getWindow());
        view->getWindow()->display();
    }
    void MenuScene::ManageInput( View * view ) {
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
