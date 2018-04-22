#pragma once

#include "View/Scene.hpp"
#include "View/View.hpp"

#include <iostream>

namespace RG {
    class MenuScene : public Scene {
        public:
            MenuScene();
            virtual ~MenuScene();
            virtual void Update( View * view );
            virtual void Render( View * view );
            virtual void ManageInput( View * view );
    };
}
