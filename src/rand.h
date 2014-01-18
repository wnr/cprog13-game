#ifndef __cprog13_game__rand__
#define __cprog13_game__rand__

#include <iostream>

namespace game {
    
    //Seed the random generator.
    void seed();
    
    // Return rand between 1 to 100 (inclusive).
    unsigned int rand(unsigned int max = 100);
    
    // Function that returns true if rand between 1 to 100 is <= the given limit.
    // Limit of 0 will always return false.
    bool happen(unsigned int limit, unsigned int max = 100);
}

#endif
