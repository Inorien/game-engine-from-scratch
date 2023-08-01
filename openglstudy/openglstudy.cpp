#include <iostream>
#include "engine.h"

int main()
{
    Engine engine{};

    std::cout << "Starting up..." << std::endl;
    try {
        engine.start();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught during engine startup: " << e.what() << std::endl;
        return -1;
    }

	engine.run();

    std::cout << "Cleaning up..." << std::endl;
    engine.shutdown();

    return 0;
}
