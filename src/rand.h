#ifndef __cprog13_game__rand__
#define __cprog13_game__rand__

namespace game {
    
    // Seed the random generator.
    void seed();
    
    // Returns random value beteen 0 and 100 (inclusive).
    unsigned int rand(unsigned int min = 0, unsigned int max = 100, bool includeMax = false);
    
    // Function that returns true if rand between 1 to 100 is <= the given limit.
    // Limit of 0 will always return false.
    bool happen(unsigned int limit, unsigned int max = 100);
}

#endif
