#include "View/Console.hpp"

namespace RG {
    namespace View {
        Console::Console() :
                HistoryPos(-1),
                m_ret("0") {
            memset(InputBuf, 0, sizeof(InputBuf));
            reclaim_focus = false;
            ScrollToBottom = false;
            m_buildIn.push_back("help");
            m_buildIn.push_back("clear");
        }

        void Console::DrawHistory() {
            //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing
            //ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, {255, 0, 0, 255});
            ImGui::BeginChild("ScrollingRegion", ImVec2(0, -25), false, ImGuiWindowFlags_HorizontalScrollbar);
            ImGuiStyle &style = ImGui::GetStyle();
            style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);


            ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);
            for (auto &it : buffer) {
                const char *item = it.c_str();
                ImVec4 col = col_default_text;
                if (strstr(item, "[error]")) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
                else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
                ImGui::PushStyleColor(ImGuiCol_Text, col);
                ImGui::TextUnformatted(item);
                ImGui::PopStyleColor();
            }
            if (ScrollToBottom)
                ImGui::SetScrollHere(1.0f);

            ImGui::EndChild();
        }

        void Console::Draw() {
            ImGui::SetNextWindowSize({320, 200}, ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos({0, 0}, ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);
            ImGui::Begin("Console");

            reclaim_focus = false;

            ImGui::Separator();
            DrawHistory();

            if (ImGui::InputText(m_ret, InputBuf, IM_ARRAYSIZE(InputBuf),
                                 ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion |
                                 ImGuiInputTextFlags_CallbackHistory,
                                 [](ImGuiTextEditCallbackData *data) -> int {
                                     Console *cons = (Console *) data->UserData;
                                     return cons->TextEditCallback(data);
                                 }, (void *) this)) {
                char *input_end = InputBuf + strlen(InputBuf);
                while (input_end > InputBuf && input_end[-1] == ' ') { input_end--; }
                *input_end = 0;
                if (InputBuf[0]) {
                    sprintf(m_ret, "%d", ExecCommand({InputBuf}));
                }
                strcpy(InputBuf, "");
                reclaim_focus = true;
            }

            ImGui::SetItemDefaultFocus();
            if (reclaim_focus)
                ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
            ImGui::End();
        }

        int Console::ExecCommand(std::string log) {
            m_history.push_back(log);
            WriteText("# " + log);
            HistoryPos = -1;

            if (log == "help") {
                for (auto &it : m_api)
                    WriteText(it.first);
                for (auto &it : m_buildIn)
                    WriteText(it);
                return 0;
            }
            if (log == "clear") {
                return ClearLogs();
            }
            for (auto &it : m_api) {
                if (it.first == log) {
                    return it.second();
                }
            }
            WriteText("[error] command not found");
            return 127;
        }

        void Console::WriteText(std::string log) {
            buffer.push_back(log);
            ScrollToBottom = true;
        }

        int Console::ClearLogs() {
            buffer.resize(0);
            return 0;
        }

        int Console::TextEditCallback(ImGuiTextEditCallbackData *data) {
            //WriteText("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
            switch (data->EventFlag) {
                case ImGuiInputTextFlags_CallbackCompletion: {
                    std::string cur{data->Buf};
                    std::string prefix;
                    const std::string *first_match = NULL;
                    int count = 0;
                    //TODO(vojta)
                    for (auto &it : m_buildIn) {
                        auto res = std::mismatch(cur.begin(), cur.end(), it.begin());
                        if (res.first == cur.end()) {
                            count++;
                            if (!first_match) {
                                first_match = &it;
                                prefix = it;
                            } else {
                                if (count == 2)
                                    WriteText("\t" + *first_match);
                                WriteText("\t" + it);
                                const std::string *s1, *s2;
                                if (prefix.size() < it.size()) {
                                    s1 = &prefix;
                                    s2 = &it;
                                } else {
                                    s2 = &prefix;
                                    s1 = &it;
                                }
                                auto pref = std::mismatch(s1->begin(), s1->end(), s2->begin());
                                prefix = prefix.substr(0,
                                                       std::min(pref.first - s1->begin(), pref.second - s2->begin()));
                            }
                        }
                    }
                    for (auto &it : m_api) {
                        auto res = std::mismatch(cur.begin(), cur.end(), it.first.begin());
                        if (res.first == cur.end()) {
                            count++;
                            if (!first_match) {
                                first_match = &(it.first);
                                prefix = it.first;
                            } else {
                                if (count == 2)
                                    WriteText("\t" + *first_match);
                                WriteText("\t" + it.first);
                                const std::string *s1, *s2;
                                if (prefix.size() < it.first.size()) {
                                    s1 = &prefix;
                                    s2 = &it.first;
                                } else {
                                    s2 = &prefix;
                                    s1 = &it.first;
                                }
                                auto pref = std::mismatch(s1->begin(), s1->end(), s2->begin());
                                prefix = prefix.substr(0,
                                                       std::min(pref.first - s1->begin(), pref.second - s2->begin()));
                            }
                        }
                    }
                    if (prefix.size()) {
                        data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int) snprintf(
                                data->Buf, (size_t) data->BufSize, "%s", prefix.c_str());
                        data->BufDirty = true;
                    }
                }
                case ImGuiInputTextFlags_CallbackHistory: {
                    const int prev_history_pos = HistoryPos;
                    if (data->EventKey == ImGuiKey_UpArrow) {
                        if (HistoryPos == -1)
                            HistoryPos = m_history.size() - 1;
                        else if (HistoryPos > 0)
                            HistoryPos--;
                    } else if (data->EventKey == ImGuiKey_DownArrow) {
                        if (HistoryPos != -1)
                            if (++HistoryPos >= (int) m_history.size())
                                HistoryPos = -1;
                    }

                    if (prev_history_pos != HistoryPos) {
                        data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int) snprintf(
                                data->Buf, (size_t) data->BufSize, "%s",
                                (HistoryPos >= 0) ? m_history[HistoryPos].c_str() : "");
                        data->BufDirty = true;
                    }
                }
            }
            return 0;
        }

        void Console::RegisterFunction(std::string name, std::function<int(void)> function) {
            m_api[name] = function;
        }
    }
}
