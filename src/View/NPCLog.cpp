#include "View/NPCLog.hpp"

namespace RG { namespace View {
    NPCLog::NPCLog( NPC::MatchingEngine * matchingEngine ) {
        matchingEngine->AddObserver( this );
    }
    void  NPCLog::AddLog(const char* fmt, ...) {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;
    }
    void    NPCLog::Draw(const char* title, bool* p_open, int x, int y) {
        ImGui::GetStyle().WindowBorderSize = 0;
        ImGui::SetNextWindowBgAlpha(0);
        ImGui::SetNextWindowSize(ImVec2(400,200), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(x,y));
        ImGui::Begin(title, p_open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs );
        ImGui::SetNextWindowBgAlpha(0.3);
        ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (Filter.IsActive())
        {
            const char* buf_begin = Buf.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::EndChild();
        ImGui::End();
    }
    void RG::View::NPCLog::onNotify(Util::Subject * subject, Util::Event event) {
        switch(event) {
            case Util::Event::ITEM_SOLD:
                {
                    NPC::MatchingEngine * me = (NPC::MatchingEngine*)subject;
                    AddLog( me->getOutput().c_str() );
                    break;
                }
            default:
                break;
        }       
    }
}}
