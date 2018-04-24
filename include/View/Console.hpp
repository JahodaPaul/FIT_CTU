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
        private:
            std::vector<std::string> buffer;
            std::vector<std::string> m_history;
            bool m_ImguiDemo;
            bool m_first;
            char InputBuf[256];
            bool reclaim_focus;
            bool ScrollToBottom;
        public:
            Console( std::map<std::string, std::function<void(void)>> *api );
            void Draw();
        private:
            int TextEditCallback(ImGuiTextEditCallbackData* );
            void DrawHistory();
            void AddLog( std::string log );
            void ClearLogs();
            int HistoryPos;
            bool ExecCommand( std::string log );
            std::map<std::string, std::function<void(void)>> *m_api;
    };
}
