#include "Util/CacheManager.hpp"

namespace RG {

    CacheManager::CacheManager(std::string folder) {
        try {
            SetStorageFolder(folder);
        }
        catch (StorageException e){
            std::cout << e.what() << std::endl;
        }
        CreateErrTexture();
    }

    CacheManager::~CacheManager() {}

    std::pair <std::string, std::shared_ptr<sf::Texture>> CacheManager::getTexture(std::string textureName) {
        std::pair <std::string, std::shared_ptr<sf::Texture>> res;

        if (m_Textures.find(textureName) != m_Textures.end()) {
            res = make_pair(m_Textures.find(textureName)->first, m_Textures.find(textureName)->second.first);
            m_Textures[textureName].second++;
        } else {
            if (!FileExists(m_StorageFolder + "/" + textureName))
                return make_pair("ErrorTexture", m_Textures["ErrorTexture"].first);
            m_Textures.insert(make_pair(textureName, make_pair(std::make_shared<sf::Texture>(sf::Texture()), 1)));
            m_Textures[textureName].first->loadFromFile(m_StorageFolder + "/" + textureName);
            res = make_pair(textureName, m_Textures[textureName].first);
        }

        return res;
    }

    std::pair <std::string, std::shared_ptr<sf::Font>> CacheManager::getFont(std::string fontName) {
        std::pair <std::string, std::shared_ptr<sf::Font>> res;

        if (m_Fonts.find(fontName) != m_Fonts.end()) {
            res = make_pair(m_Fonts.find(fontName)->first, m_Fonts.find(fontName)->second.first);
            m_Fonts[fontName].second++;
        } else {
            if (!FileExists(m_StorageFolder + "/" + fontName))
                std::cout << "Font file missing!" << std::endl;
            m_Fonts.insert(make_pair(fontName, make_pair(std::make_shared<sf::Font>(sf::Font()), 1)));
            m_Fonts[fontName].first->loadFromFile(m_StorageFolder + "/" + fontName);
            res = make_pair(fontName, m_Fonts[fontName].first);
        }

        return res;
    }

    bool CacheManager::deleteTexture(std::string textureName) {
        if (m_Textures.find(textureName) == m_Textures.end())
            return false;

        m_Textures[textureName].second--;

        if (m_Textures[textureName].second == 0)
            m_Textures.erase(textureName);

        return true;
    }

    bool CacheManager::deleteFont(std::string fontName) {
        if (m_Fonts.find(fontName) == m_Fonts.end())
            return false;

        m_Fonts[fontName].second--;

        if (m_Fonts[fontName].second == 0)
            m_Fonts.erase(fontName);

        return true;
    }

    void CacheManager::SetStorageFolder(std::string folder) {
        if(!FileExists(folder))
            throw StorageException(folder);
        m_StorageFolder = folder;
    }

    bool CacheManager::FileExists(std::string fileName) {
        std::ifstream f(fileName);
        return f.good();
    }

    void CacheManager::CreateErrTexture() {
        sf::RenderTexture render;
        render.create(800,600);
        render.clear(sf::Color::Magenta);
        std::string textureName = "ErrorTexture";
        m_Textures.insert( std::make_pair( textureName, std::make_pair(std::make_shared<sf::Texture>(render.getTexture()), 1)) );
    }

}