#include "View/View.hpp"

namespace RG {
    namespace View {
        View::View(GameController *controller, std::pair<int,int> windowSize, const char *windowTitle)
                : m_gameControllet(controller),
                  m_ImguiDemo(false) {
            m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowSize.first, windowSize.second),
                                                          windowTitle, sf::Style::Default,
                                                          sf::ContextSettings{0u, 0u, 4u, 1u, 1u, 0u, false});
            //synchromize refresh rate with monitor refresh rate
            m_window->setVerticalSyncEnabled(true);

            // Invert y axis and zoom in
            //m_view.reset(sf::FloatRect(0, windowSize.y, 2*windowSize.x, 2*-windowSize.y));

//            m_window->setVerticalSyncEnabled(true);
            m_window->setFramerateLimit(60);

            // Apply setting
            //m_window.setView(m_view);

            m_activeScene = SCENE::MENU_SCENE;
            m_mapOfGameScenes[SCENE::MENU_SCENE] = std::shared_ptr<Scene>(new MenuScene());
            m_mapOfGameScenes[SCENE::GAME_SCENE] = std::shared_ptr<Scene>(new GameScene());

            //initialize imgui
            ImGui::SFML::Init(*m_window);
            ImGuiIO &io = ImGui::GetIO();
            io.KeyMap[ImGuiKey_Space] = sf::Keyboard::Return;
            io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

            m_console.RegisterFunction("quit", std::function<int(void)>([this]() { return m_gameControllet->Quit(); }));
            m_console.RegisterFunction("imgui_demo", std::function<int(void)>([this]() {
                m_ImguiDemo = !m_ImguiDemo;
                return 0;
            }));
            m_console.RegisterFunction("go_to_game_scene", std::function<int(void)>([this]() {
                m_gameControllet->GoToGame();
                return 0;
            }));
            m_console.RegisterFunction("go_to_menu_scene", std::function<int(void)>([this]() {
                m_gameControllet->GoToMainMenu();
                return 0;
            }));

            room = std::make_shared<RG::View::Room>();

            m_soundManager.PlayMusic("frankum");
        }

        View::~View() {}

        void View::ManageInput() {
            m_mapOfGameScenes[m_activeScene]->ManageInput(this);
        }

        void View::Update() {
            m_mapOfGameScenes[m_activeScene]->Update(this);
        }

        void View::Render() {
            //ImGui
            ImGui::SFML::Update(*m_window, m_clock.restart());
            m_window->clear({0, 0, 0, 255});

            //FPS counter
            ImGui::SetNextWindowPos({m_window->getSize().x - 90.f, 0});
            ImGui::SetNextWindowSize({90, 20});
            ImGui::Begin("FPS", NULL,
                         ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
            ImGui::End();

            //DEBUG
            if (m_ImguiDemo)
                ImGui::ShowDemoWindow();
            m_console.Draw();

            m_mapOfGameScenes[m_activeScene]->Render(this);

            //ImGui
            ImGui::SFML::Render(*m_window);
            //display window content

            m_window->display();
        }

        std::shared_ptr<sf::RenderWindow> View::getWindow() {
            return m_window;
        }

        GameController *View::getGameController() const {
            return m_gameControllet;
        }

        const sf::Clock &View::getClock() const {
            return m_clock;
        }

        void View::setActiveView(SCENE scene) {
            m_activeScene = scene;
        }

        void View::SetPlayer() {
            player = std::make_shared<Player>();
            player->SetPosition(m_window->getView().getSize().x/2,m_window->getView().getSize().y/2);
        }

        std::shared_ptr<RG::View::Player> View::GetPlayer() {
            return player;
        }

        void View::UpdatePlayer(float relativeMoveX, float relativeMoveY,float absoluteX, float absoluteY) {
            player->UpdatePlayer(relativeMoveX, relativeMoveY,absoluteX,absoluteY);
        }

        void View::DrawPlayer() {
            player->SetPlayerScale(m_window->getView().getSize().x,m_window->getView().getSize().y);
            player->DrawPlayer(*this->getWindow());
        }

        void View::DrawRoom() {
            room->DrawRoom(this->getGameController()->GetFloorLevel(),this->getGameController()->GetRoomId(),*this->getWindow());
//            room->SetSpriteScale((float)m_window->getSize().x,(float)m_window->getSize().y);
            room->SetSpriteScale(m_window->getView().getSize().x,m_window->getView().getSize().y);
            std::vector<bool> temporary = m_gameControllet->GetRoomDoors();
            room->DrawDoor(*this->getWindow(), temporary[0],temporary[1],temporary[2],temporary[3],m_window->getView().getSize().x,m_window->getView().getSize().y);
        }

        const sf::View View::GetView() {
            return m_window->getView();
        }
    }
}
