#include "Util/CacheManager.cpp"

int main(void){

    CacheManager cacheManager;

    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr;
    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr2;
    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr3;
    std::pair<std::string, std::shared_ptr<sf::Texture>> txtr4;

    txtr = cacheManager.getTexture("bg.png");
    txtr2 = cacheManager.getTexture("bg.png");
    txtr3 = cacheManager.getTexture("bg.png");
    txtr4 = cacheManager.getTexture("bg.png");

    cacheManager.deleteTexture("bg.png");
    cacheManager.deleteTexture("bg.png");
    cacheManager.deleteTexture("bg.png");
    cacheManager.deleteTexture("bg.png");

    return 0;
}