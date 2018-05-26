#include "View/Gui.hpp"
#include "View/View.hpp"
#include "Model/Entity.hpp"
#include "Model/Model.hpp"

namespace RG { namespace View {
    Gui::Gui( View * view ) {
        view->getGameController()->getModel().AddObserver( this );
        Model::Entity *player = &view->getGameController()->getModel().GetPlayer();

        floor = "Floor: " + std::to_string(view->getGameController()->getModel().GetFloorLevel());

        attack = "Attack: " + std::to_string(player->GetAttackLevel());
        playerName = "Vojta";

        maxHealth = 100;
        currentHealth = player->GetHP();
        healtPart = (float)currentHealth / maxHealth;
        sprintf(healthBuf, "%d/%d", (int)(currentHealth), maxHealth);


        XPToNextLevel = 200;
        currentXP = 0;
        XPpart = (float)currentXP / XPToNextLevel;
        sprintf(xpBuf, "%d/%d", (int)(currentXP), XPToNextLevel);

        player->AddObserver( this );
    }
    void Gui::Draw() {
        ImGui::GetStyle().WindowBorderSize = 3;
        ImGui::GetStyle().Colors[ImGuiCol_::ImGuiCol_PlotHistogram] = {0.8,0.2,0.2,0.8};
        ImGui::SetNextWindowBgAlpha(0.2);
        ImGui::SetNextWindowSize({200,0});
        ImGui::SetNextWindowPos({0,20});

        ImGui::Begin("", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );

        ImGui::Text(floor.c_str());

        ImGui::Text(playerName.c_str());

        ImGui::Text("HP: ");
        ImGui::SameLine();
        ImGui::ProgressBar(healtPart, ImVec2(0.f,0.f), healthBuf);

        ImGui::GetStyle().Colors[ImGuiCol_::ImGuiCol_PlotHistogram] = {0.6,0.6,0.2,0.8};
        ImGui::Text("XP: ");
        ImGui::SameLine();
        ImGui::ProgressBar(XPpart, ImVec2(0.f,0.f), xpBuf);

        ImGui::Text(attack.c_str());

        ImGui::End();
        ImGui::GetStyle().WindowBorderSize = 0;
    }
    void Gui::onNotify(Util::Subject * subject, Util::Event event) {
        switch(event) {
            case Util::Event::FLOOR_CHANGE:
                {
                    floor = "Floor: " + std::to_string(((Model::Model*)subject)->GetFloorLevel());
                    break;
                }
            case Util::Event::WINDOW_RESIZE:
                {
                    break;
                }
            case Util::Event::ENTITY_DEAD:
                {
                    break;
                }
            case Util::Event::ENTITY_DAMAGED:
                {
                    Model::Entity *player = (Model::Entity*)subject;
                    currentHealth = player->GetHP();
                    healtPart = (float)currentHealth / maxHealth;
                    sprintf(healthBuf, "%d/%d", (int)(currentHealth), maxHealth);
                    break;
                }
            default:
                break;
        }       
    }
}}
