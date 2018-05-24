#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include "Util/Observer.hpp"
#include "NPC/MatchingEngine.hpp"

namespace RG { namespace View {
    class NPCLog : public Util::Observer {
        public:
            NPCLog( NPC::MatchingEngine * matchingEngine );
            void    Clear()     { Buf.clear(); LineOffsets.clear(); }

            void    AddLog(const char* fmt, ...) IM_FMTARGS(2);

            void    Draw(const char* title, bool* p_open = NULL, int x = 0, int y = 0);
            void onNotify(Util::Subject * subject, Util::Event event);
        private:
            ImGuiTextBuffer     Buf;
            ImGuiTextFilter     Filter;
            ImVector<int>       LineOffsets;        // Index to lines offset
            bool                ScrollToBottom;
    };

}}
