#pragma once

#include <string>

#include "Util/Observer.hpp"

namespace RG { namespace View {
    class View;
    class Gui : public Util::Observer {
        public:
            Gui( View * view );
            void Draw();
            void onNotify(Util::Subject * subject, Util::Event event) override;
        private:
            std::string playerName;
            std::string attack;
            int maxHealth;
            int currentHealth;
            float healtPart;

            int XPToNextLevel;
            int currentXP;
            float XPpart;

            char healthBuf[32];
            char xpBuf[32];
    };
}}
