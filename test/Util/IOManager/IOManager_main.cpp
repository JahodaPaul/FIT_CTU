#include <Util/IOManager.hpp>

using namespace RG;

int main(void){

    IOManager manager;

    std::cout << "The A key before mapping: " << manager.GetMapped(sf::Keyboard::A) << std::endl;

    manager.MapKey(sf::Keyboard::A, sf::Keyboard::Left);

    std::cout << "The A key after mapping: " << manager.GetMapped(sf::Keyboard::A) << std::endl;

    return 0;

}