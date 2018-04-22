#pragma once

namespace RG {
    class View;
    class Scene {
        public:
            Scene();
            virtual ~Scene();
            virtual void Update( View * view );
            virtual void Render( View * view );
            virtual void ManageInput( View * view );
    };
}
