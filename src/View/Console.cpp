#include "View/Console.hpp"

namespace RG {
    Console::Console( std::map<std::string, std::function<void(void)>> *api) :
        HistoryPos( -1 ),
        m_api ( api )
    {
        memset(InputBuf, 0, sizeof(InputBuf));
        reclaim_focus = false;
        ScrollToBottom = false;
    }
    void Console::DrawHistory() {
        //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing
        //ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, {255, 0, 0, 255});
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -200), false, ImGuiWindowFlags_HorizontalScrollbar);
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);


        ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);
        for (auto & it : buffer )
        {
            const char* item = it.c_str();
            ImVec4 col = col_default_text;
            if (strstr(item, "[error]")) col = ImColor(1.0f,0.4f,0.4f,1.0f);
            else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f,0.78f,0.58f,1.0f);
            ImGui::PushStyleColor(ImGuiCol_Text, col);
            ImGui::TextUnformatted(item);
            ImGui::PopStyleColor();
        }
        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);

        ImGui::EndChild();
    }
    void Console::Draw() {
        ImGui::SetNextWindowSize(ImVec2(520,600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Console");

        reclaim_focus = false;

        ImGui::Separator();
        DrawHistory();

        if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_CallbackCompletion|ImGuiInputTextFlags_CallbackHistory,
                    [](ImGuiTextEditCallbackData* data) -> int {
                        Console* cons = (Console*)data->UserData;
                        return cons->TextEditCallback( data );
                    }, (void*)this))
        {
            char* input_end = InputBuf+strlen(InputBuf);
            while (input_end > InputBuf && input_end[-1] == ' ') { input_end--; } *input_end = 0;
            if (InputBuf[0])
                ExecCommand({InputBuf});
            strcpy(InputBuf, "");
            reclaim_focus = true;
        }

        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
        ImGui::End();
    }
    bool Console::ExecCommand( std::string log ) {
        m_history.push_back( log );
        AddLog( "# " + log );
        HistoryPos = -1;

        if ( log == "help" ) {
            for ( auto & it : *m_api )
                AddLog( it.first );
            return true;
        }
        for ( auto & it : *m_api ) {
            if ( it.first == log ) {
                it.second();
                return true;
            }
        }
        AddLog( "[error] command not found" );
        return false;
    }
    void Console::AddLog( std::string log ) {
        buffer.push_back( log );
        ScrollToBottom = true;
    }
    void Console::ClearLogs() {
        buffer.resize( 0 );
    }
    int Console::TextEditCallback(ImGuiTextEditCallbackData* data) {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag) {
            case ImGuiInputTextFlags_CallbackCompletion:
                {
                }
            case ImGuiInputTextFlags_CallbackHistory:
                {
                    const int prev_history_pos = HistoryPos;
                    if (data->EventKey == ImGuiKey_UpArrow)
                    {
                        if (HistoryPos == -1)
                            HistoryPos = m_history.size() - 1;
                        else if (HistoryPos > 0)
                            HistoryPos--;
                    }
                    else if (data->EventKey == ImGuiKey_DownArrow)
                    {
                        if (HistoryPos != -1)
                            if (++HistoryPos >= m_history.size())
                                HistoryPos = -1;
                    }

                    if (prev_history_pos != HistoryPos)
                    {
                        data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (HistoryPos >= 0) ? m_history[HistoryPos].c_str() : "");
                        data->BufDirty = true;
                    }
                }
        }
        return 0;
    }
}
