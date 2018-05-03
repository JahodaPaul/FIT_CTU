#include <Util/IOManager.hpp>

namespace RG{

    IOManager::IOManager(std::string dir, std::string f): storageDir(dir), file(f){
        std::cout << "Storage directory: " << dir << std::endl;
        std::cout << "Mapping file: " << f << std::endl;

        keyArr.push_back(sf::Keyboard::Right);

        std::cout << "Key: " << sf::Keyboard::Right << std::endl;
        std::cout << "Mapped key: " << keyArr[0] << std::endl;

    }

    IOManager::~IOManager() {}

    sf::Keyboard::Key IOManager::GetMapped(sf::Keyboard::Key key){
        return keyArr[key];
    }

    void IOManager::MapKey(sf::Keyboard::Key toMap, sf::Keyboard::Key mapRes){
        keyArr[toMap] = mapRes;
    }

    void IOManager::Serialize(){

    }

    void IOManager::Deserialize(){

    }

    void IOManager::Draw(){

    }

    void IOManager::SetStorageDir(std::string dir){
        storageDir = dir;
    }

    void IOManager::SetFile(std::string f){
        file = f;
    }

}