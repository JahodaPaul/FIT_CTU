#include <iostream>

#include "View/Player.hpp"
#include "../include/Controller/GameController.hpp"

int main() {
    std::cout << "main" << std::endl;
    RG::GameController g;
    g.Run();
}
