#ifndef __cprog13_game__rand__
#define __cprog13_game__rand__

namespace game {
    
    //Seed the random generator.
    void seed();
    
    // Return rand between 1 to 100 if inclusive. 0 to 99 if exclusive.
    unsigned int rand(unsigned int max = 100, bool inclusive = false);
    
    // Function that returns true if rand between 1 to 100 is <= the given limit.
    // Limit of 0 will always return false.
    bool happen(unsigned int limit, unsigned int max = 100);
}

#endif
