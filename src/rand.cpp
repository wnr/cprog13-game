#include "rand.h"

#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <cstdlib>

void game::seed() {
    srand((unsigned int)time(NULL));
}

unsigned int game::rand(unsigned int min, unsigned int max, bool includeMax) {
    if(max < min) {
        throw std::invalid_argument("max cannot be lower than min");
    }
    
    if(max >= RAND_MAX) {
        throw std::invalid_argument("max cannot be higher than MAX_RAND.");
    }
    
    if(max == min) {
        return min;
    }
    
    unsigned int diff = max - min;
    
    return (unsigned int)( min + (std::rand() % (diff + (includeMax ? 1 : 0))));
}

bool game::happen(unsigned int limit, unsigned int max) {
    return game::rand(1, max) <= limit;
}