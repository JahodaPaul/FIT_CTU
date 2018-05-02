#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"

#include <iostream>

namespace RG {
    namespace View {
        class GameScene : public Scene {
        public:
            GameScene();

            virtual ~GameScene();

            virtual void Update(View *view);

            virtual void Render(View *view);

            virtual void ManageInput(View *view);
        };
    }
}
