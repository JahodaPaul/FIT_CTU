#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <functional>

#include "imgui.h"
#include "imgui-SFML.h"

namespace RG {
    namespace View {
        //! \class Console
        /*!
         *  \brief Console class
         *  This is virtual konsole inside our game. It can be used to register functions and call them via console GUI in game.
         *  This is usefull primary for debuging purposes.
         */
        class Console {
        public:
            //! A constructor
            Console();

            //! register new function into console API
            /*!
             * \param name name of registered function, this can be used to call this function
             * \param function std function of typee int(void)
             */
            void RegisterFunction(std::string name, std::function<int(void)> function);

            //! Write text into console.
            /*!
             * \param log Text to be written
             */
            void WriteText(std::string log);

            //! Draw console this should be called every frame.
            void Draw();

        private:
            int TextEditCallback(ImGuiTextEditCallbackData *);

            void DrawHistory();

            int ClearLogs();

            int HistoryPos;

            int ExecCommand(std::string log);

        private:
            std::vector<std::string> buffer;
            std::vector<std::string> m_history;
            bool m_ImguiDemo;
            bool m_first;
            char InputBuf[256];
            bool reclaim_focus;
            bool ScrollToBottom;
            char m_ret[12];
            std::map<std::string, std::function<int(void)>> m_api;
            std::vector<std::string> m_buildIn;
        };
    }
}
