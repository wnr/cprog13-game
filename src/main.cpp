
#include <iostream>
#include <sstream>

#include "Engine.h"

#include "OwningStorage.h"
#include "rand.h"

using namespace game;

int main(int argc, const char * argv[])
{
    Engine::getInstance()->run();
    
    return 0;
}
