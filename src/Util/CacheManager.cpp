#include "Util/CacheManager.hpp"

namespace RG {
    CacheManager::CacheManager(std::string folder) {
        SetStorageFolder(folder);
    }

    CacheManager::~CacheManager() {}

    std::pair <std::string, std::shared_ptr<sf::Texture>> CacheManager::getTexture(std::string textureName) {
        std::pair <std::string, std::shared_ptr<sf::Texture>> res;

        if (textures.find(textureName) != textures.end()) {
            res = make_pair(textures.find(textureName)->first, textures.find(textureName)->second.first);
            textures[textureName].second++;
        } else {
            textures.insert(make_pair(textureName, make_pair(std::make_shared<sf::Texture>(sf::Texture()), 1)));
            textures[textureName].first->loadFromFile(storageFolder + "/" + textureName);
            res = make_pair(textureName, textures[textureName].first);
        }

        return res;
    }

    std::pair <std::string, std::shared_ptr<sf::Font>> CacheManager::getFont(std::string fontName) {
        std::pair <std::string, std::shared_ptr<sf::Font>> res;

        if (fonts.find(fontName) != fonts.end()) {
            res = make_pair(fonts.find(fontName)->first, fonts.find(fontName)->second.first);
            fonts[fontName].second++;
        } else {
            fonts.insert(make_pair(fontName, make_pair(std::make_shared<sf::Font>(sf::Font()), 1)));
            fonts[fontName].first->loadFromFile(storageFolder + "/" + fontName);
            res = make_pair(fontName, fonts[fontName].first);
        }

        return res;
    }

    bool CacheManager::deleteTexture(std::string textureName) {
        if (textures.find(textureName) == textures.end())
            return false;

        textures[textureName].second--;

        if (textures[textureName].second == 0)
            textures.erase(textureName);

        return true;
    }

    bool CacheManager::deleteFont(std::string fontName) {
        if (fonts.find(fontName) == fonts.end())
            return false;

        fonts[fontName].second--;

        if (fonts[fontName].second == 0)
            fonts.erase(fontName);

        return true;
    }

    void CacheManager::SetStorageFolder(std::string folder) {
        struct stat info;
        if (stat(folder.c_str(), &info) < 0)
            mkdir(folder.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH);
        storageFolder = folder;
    }
}