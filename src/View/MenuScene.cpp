#include "View/MenuScene.hpp"

namespace RG {
    MenuScene::MenuScene() :
        m_showSetting( false ),
        m_showMenu( true ),
        m_notReset( true )
    {
        std::cout <<"menu scene constructor" << std::endl;
    }
    MenuScene::~MenuScene() {}
    void MenuScene::Update( View * view ) {
        if ( !m_notReset ) {
            m_notReset = true;
            m_showSetting = false;
            m_showMenu = true;
        }
    }
    void MenuScene::Render( View * view ) {

        ImGui::GetStyle().WindowBorderSize = 2;
        ImGui::SetNextWindowBgAlpha(0);
        ImGui::SetNextWindowPos(ImVec2(view->getWindow()->getSize().x / 2  - m_menuWidth/2, view->getWindow()->getSize().y / 2 - m_menuHeight/2));
        ImGui::SetNextWindowSize({m_menuWidth,m_menuHeight});

        if ( m_showMenu ) {
            ImGui::Begin("", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove );
            if (ImGui::Button("New Game", ImVec2(m_itemWidth,m_itemHeight))) {
                view->getGameController()->GoToGame();
            }
            if (ImGui::Button("Higscores", ImVec2(m_itemWidth,m_itemHeight))) { }
            if (ImGui::Button("Settings", ImVec2(m_itemWidth,m_itemHeight))) { m_showSetting = true; m_showMenu = false; }
            if (ImGui::Button("Exit", ImVec2(m_itemWidth,m_itemHeight)))
                view->getGameController()->Quit();
            ImGui::End();
        }

        if ( m_showSetting ) {
            ImGui::SetNextWindowSize({m_settingsWidth,m_settingsHeight}, ImGuiCond_Once );
            ImGui::SetNextWindowPos(ImVec2(view->getWindow()->getSize().x / 2 - m_settingsWidth / 2,view->getWindow()->getSize().y / 2 - m_settingsHeight / 2));
            ImGui::SetNextWindowCollapsed(false, ImGuiCond_Once );
            ImGui::Begin("Settings", &m_notReset, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove );
            if ( ImGui::CollapsingHeader("Keybindings") ) {
                view->m_IOManager.Draw();
            }
            if ( ImGui::CollapsingHeader("test1") ) {
                ImGui::BeginChild("Test1");
                ImGui::Text("Test1");
                ImGui::EndChild();
            }
            ImGui::End();
        }
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
