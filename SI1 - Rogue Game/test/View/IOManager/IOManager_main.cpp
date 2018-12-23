#include <View/IOManager.hpp>

using namespace RG;

int main(void){

    std::cout << "Testing the default key mapping." << std::endl;

    IOManager firstManager;
    remove("keys/mapping.txt");
    std::cout << "The A key before mapping: " << firstManager.GetMapped(sf::Keyboard::A) << std::endl;
    firstManager.MapKey(sf::Keyboard::A, sf::Keyboard::Left);
    std::cout << "The A key after mapping: " << firstManager.GetMapped(sf::Keyboard::A) << std::endl;

    std::cout << "\nTesting mapping loaded from file." << std::endl;

    IOManager secondManager;
    std::cout << "The A key: " << secondManager.GetMapped(sf::Keyboard::A) << std::endl;
    secondManager.MapKey(sf::Keyboard::D, sf::Keyboard::Right);
    std::cout << "The D key: " << secondManager.GetMapped(sf::Keyboard::D) << std::endl;

    std::cout << "\nTesting changing the storage file and directory." << std::endl;

    IOManager thirdManager;
    std::cout << "The A key before changing the file: " << thirdManager.GetMapped(sf::Keyboard::A) << std::endl;
    std::cout << "The D key before changing the file: " << thirdManager.GetMapped(sf::Keyboard::D) << std::endl;
    thirdManager.SetFile("userMapping.txt");
    std::cout << "The A key after changing the file: " << thirdManager.GetMapped(sf::Keyboard::A) << std::endl;
    std::cout << "The D key after changing the file: " << thirdManager.GetMapped(sf::Keyboard::D) << std::endl;
    thirdManager.SetStorageDir("new_keys");
    std::cout << "The A key after changing the directory: " << thirdManager.GetMapped(sf::Keyboard::A) << std::endl;
    std::cout << "The D key after changing the directory: " << thirdManager.GetMapped(sf::Keyboard::D) << std::endl;

    return 0;

}