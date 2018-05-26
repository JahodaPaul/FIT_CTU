#include <View/IOManager.hpp>

namespace RG{ namespace View {

    IOManager::IOManager(std::string dir, std::string fileName): m_StorageDir(dir), m_File(fileName){
        if(FileExists(m_StorageDir+"/"+m_File)){
            Open();
            Deserialize();
        }
        else{
            Open();
            SetDefaultKeys();
            Serialize();
        }
    }

    IOManager::~IOManager(){
        Close();
    }

    sf::Keyboard::Key IOManager::GetMapped(sf::Keyboard::Key key) const {
        return m_KeyArr[key];
    }

    void IOManager::MapKey(sf::Keyboard::Key toMap, sf::Keyboard::Key mapRes){
        m_KeyArr[toMap] = mapRes;
        Serialize();
    }

    void IOManager::Serialize(){
        Close();
        remove((m_StorageDir+"/"+m_File).c_str());
        Open();
        for(unsigned i = 0; i < m_KeyArr.size(); i++){
            if(i != m_KeyArr.size()-1)
                m_Stream << m_KeyArr[i] << " ";
            else
                m_Stream << m_KeyArr[i];
            m_Stream << std::endl;
        }
    }

    void IOManager::Deserialize(){
        std::string serialized;
        m_KeyArr.clear();
        while(m_Stream >> serialized)
            m_KeyArr.push_back((sf::Keyboard::Key) stoi(serialized));
    }

    void IOManager::Draw(){
        ImGui::BeginChild("Key settings", {0, 120});
        ImGui::Text("Key settings");
        static ImGuiComboFlags keyFlags = 0;
        static ImGuiComboFlags valFlags = 0;
        static const char * currentKey = m_Keys[0];
        static int currentKeyInx = 0;
        static const char * currentVal = m_Keys[0];
        static int currentValInx = 0;

        if (ImGui::BeginCombo("Key", currentKey, keyFlags))
        {
            for (int n = 0; n < IM_ARRAYSIZE(m_Keys); n++)
            {
                bool is_selected = (currentKey == m_Keys[n]);
                if (ImGui::Selectable(m_Keys[n], is_selected)){
                    currentKey = m_Keys[n];
                    currentKeyInx = n;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if (ImGui::BeginCombo("Value", currentVal, valFlags))
        {
            for (int n = 0; n < IM_ARRAYSIZE(m_Keys); n++)
            {
                bool is_selected = (currentVal == m_Keys[n]);
                if (ImGui::Selectable(m_Keys[n], is_selected)){
                    currentVal = m_Keys[n];
                    currentValInx = n;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if(ImGui::Button("Set", {100,50})){
            MapKey((sf::Keyboard::Key) currentKeyInx,(sf::Keyboard::Key) currentValInx);
        }

        ImGui::EndChild();
    }

    void IOManager::SetDefaultKeys(){
        //TODO causes crashes
        //mainLog.Info("Key count: " + sf::Keyboard::KeyCount);
        for(int i = 0; i < sf::Keyboard::KeyCount; i++)
            m_KeyArr.push_back((sf::Keyboard::Key) i);
        mainLog.Info("Setting default keys.");
    }

    void IOManager::SetStorageDir(std::string dir){
        m_StorageDir = dir;
        Serialize();
    }

    void IOManager::SetFile(std::string fileName){
        m_File = fileName;
        Serialize();
    }

    bool IOManager::Open(){
        if(!m_Stream.is_open()){
            std::string fullPath = m_StorageDir +"/"+ m_File;
            try{
                m_Stream.open(fullPath, std::ios::out | std::ios::app | std::ios::in);
            }
            catch(std::exception & e){
                return false;
            }
        }
        return true;
    }

    bool IOManager::Close(){
        try {
            if(m_Stream.is_open()){
                m_Stream.close();
                return !m_Stream.is_open();
            }
            else
                return false;
        }
        catch (std::exception &e) {
            return false;
        }
    }

    bool IOManager::FileExists(std::string fileName) {
        std::ifstream f(fileName);
        return f.good();
    }

} }
