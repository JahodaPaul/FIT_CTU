#include <Util/IOManager.hpp>

namespace RG{

    IOManager::IOManager(std::string dir, std::string fileName): m_StorageDir(dir), m_File(fileName){
        std::cout << "Storage directory: " << m_StorageDir << std::endl;
        std::cout << "Mapping file: " << m_File << std::endl;

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

    sf::Keyboard::Key IOManager::GetMapped(sf::Keyboard::Key key){
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
        for(unsigned i = 0; i < m_KeyArr.size(); i++)
            if(i != m_KeyArr.size()-1)
                m_Stream << m_KeyArr[i] << " ";
            else
                m_Stream << m_KeyArr[i];
            m_Stream << std::endl;
    }

    void IOManager::Deserialize(){
        std::string serialized;
        m_KeyArr.clear();
        while(m_Stream >> serialized)
            m_KeyArr.push_back((sf::Keyboard::Key) stoi(serialized));
    }

    void IOManager::Draw(){

    }

    void IOManager::SetDefaultKeys(){
        for(int i = 0; i < sf::Keyboard::KeyCount; i++)
            m_KeyArr.push_back((sf::Keyboard::Key) i);
        std::cout << "Setting default keys." << std::endl;
    }

    void IOManager::SetStorageDir(std::string dir){
        m_StorageDir = dir;
    }

    void IOManager::SetFile(std::string fileName){
        m_File = fileName;
    }

    bool IOManager::Open(){
        if(!m_Stream.is_open()){
            std::string fullPath = m_StorageDir +"/"+ m_File;
            try{
                m_Stream.open(fullPath, std::ios::out | std::ios::app | std::ios::in);
            }
            catch(std::exception e){
                return false;
            }
        }
        std::cout << "Stream opened!" << std::endl;
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

}