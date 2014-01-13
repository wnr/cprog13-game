#include <iostream>
#include "Engine.h"

using namespace game;


int main(int argc, const char * argv[])
{
    Engine::getInstance().run();
    
    return 0;
}