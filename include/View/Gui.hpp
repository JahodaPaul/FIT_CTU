#pragma once

#include <string>

#include "Util/Observer.hpp"

namespace RG { namespace View {
    class View;
    /**
     * \class Gui
     * \brief Graphical user interface
     *
     * This class is used to present data to player, such as current HP, XP, name...
     * 
     */
    class Gui : public Util::Observer {
        public:
            /**
             * \brief Constructor
             *
             * @param view pointer to View
             */
            Gui( View * view );

            /**
             * \brief Draw Gui
             */
            void Draw();

            /**
             * \brief get X compound of player speed ( this was store using SetPlayerSpeedX )
             */
            void onNotify(Util::Subject * subject, Util::Event event) override;
        private:
            std::string playerName;
            std::string attack;
            std::string floor;

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
