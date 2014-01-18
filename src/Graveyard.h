#ifndef __cprog13_game__HealthEnvironment__
#define __cprog13_game__HealthEnvironment__

#include "Environment.h"

namespace game {
    class Graveyard : public Environment {
        const unsigned int ghostSpawnProb;
        
    public:
        Graveyard(std::string name, std::string desc, unsigned int ghostSpawnProb);
        Graveyard(const Graveyard & env);
        Graveyard(Graveyard && env);
        virtual ~Graveyard();
        
        void update();
    };
}

#endif
