
#include <iostream>
#include <sstream>

#include "Engine.h"

#include "OwningStorage.h"
#include "rand.h"

using namespace game;

int main(int argc, const char * argv[])
{    
    try
    {
        Engine::getInstance()->run();
    }
    catch(std::exception & ex)
    {
        std::cout << std::endl << std::endl << "EXCEPTION: " << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}
