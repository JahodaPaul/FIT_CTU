#include "Util/TextureManager.hpp"

namespace RG{
    TextureManager::TextureManager() {}

    TextureManager::~TextureManager() {}

    std::pair<std::string, std::shared_ptr<sf::Texture>> TextureManager::getTexture(std::string textureName)
    {
        std::pair<std::string, std::shared_ptr<sf::Texture>> res;

        if(textures.find(textureName) != textures.end()){
            res = make_pair(textures.find(textureName)->first, textures.find(textureName)->second.first);
            textures[textureName].second++;
        }
        else{
            textures.insert( make_pair( textureName, make_pair(std::make_shared<sf::Texture>(sf::Texture()), 1) ) );
            textures[textureName].first->loadFromFile(textureName);
            res = make_pair(textureName, textures[textureName].first);
        }

        return res;
    }

    bool TextureManager::deleteTexture(std::string textureName)
    {
        if(textures.find(textureName) == textures.end())
            return false;

        textures[textureName].second--;

        if(textures[textureName].second == 0)
            textures.erase(textureName);

        return true;
    }

    int main(void){

        /*TextureManager txtrManager;

        std::pair<std::string, std::shared_ptr<sf::Texture>> txtr;
        std::pair<std::string, std::shared_ptr<sf::Texture>> txtr2;
        std::pair<std::string, std::shared_ptr<sf::Texture>> txtr3;
        std::pair<std::string, std::shared_ptr<sf::Texture>> txtr4;

        txtr = txtrManager.getTexture("bg.png");
        txtr2 = txtrManager.getTexture("bg.png");
        txtr3 = txtrManager.getTexture("bg.png");
        txtr4 = txtrManager.getTexture("bg.png");

        txtrManager.deleteTexture("bg.png");
        txtrManager.deleteTexture("bg.png");
        txtrManager.deleteTexture("bg.png");
        txtrManager.deleteTexture("bg.png");*/

        return 0;

    }
}