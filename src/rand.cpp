#include "rand.h"

#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <cstdlib>

void game::seed() {
    srand((unsigned int)time(NULL));
}

unsigned int game::rand(unsigned int max) {
    if(max >= RAND_MAX) {
        throw std::invalid_argument("max cannot be higher than MAX_RAND.");
    }
    
    return (unsigned int)((std::rand() % max) + 1); //Generates number between 1 and max inclusively.
}

bool game::happen(unsigned int limit, unsigned int max) {
    return game::rand(max) <= limit;
}