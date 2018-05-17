#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"

#include "View/Player.hpp"
#include "View/Room.hpp"

#include <iostream>

namespace RG {
    namespace View {
        class GameScene : public Scene {
        public:
            GameScene();

            virtual ~GameScene();

            virtual void Update(View *view, float timeElapsed);

            virtual void Render(View *view);

            virtual void ManageInput(View *view);
        private:
            std::shared_ptr<RG::View::Player> GetPlayer();

            void SetPlayer();

            void SetPlayerSpeedY(float);

            void SetPlayerSpeedX(float);

            float GetPlayerSpeedY();

            float GetPlayerSpeedX();

            void UpdatePlayer(View * view, float timeElapsed);

            void DrawPlayer(View *view);

            void DrawRoom(View *view);


            std::shared_ptr<RG::View::Player> player;
            std::shared_ptr<RG::View::Room> room;
        };
    }
}
