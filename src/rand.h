#ifndef __cprog13_game__rand__
#define __cprog13_game__rand__

namespace game {
    
    // Seed the random generator.
    void seed();
    
    //Goes from 0 to 99 (default).
    unsigned int rand(unsigned int max = 100, bool includeMax = false);
    
    // Choose the fuck yourself.
    unsigned int rand(unsigned int min, unsigned int max, bool includeMax = false);
    
    // Function that returns true if rand between 1 to 100 is <= the given limit.
    // Limit of 0 will always return false.
    bool happen(unsigned int limit, unsigned int max = 100);
}

#endif
