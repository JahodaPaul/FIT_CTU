#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <functional>

#include "imgui.h"
#include "imgui-SFML.h"

namespace RG {
    class Console {
        public:
            Console();
            void RegisterFunction( std::string name, std::function<int(void)> function );
            void WriteText( std::string log );
            void Draw();
        private:
            int TextEditCallback(ImGuiTextEditCallbackData* );
            void DrawHistory();
            int ClearLogs();
            int HistoryPos;
            int ExecCommand( std::string log );
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
