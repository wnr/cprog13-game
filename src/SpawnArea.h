#ifndef __cprog13_game__SpawnArea__
#define __cprog13_game__SpawnArea__

#include "Environment.h"

namespace game {
    class SpawnEntry {
    public:
        const std::shared_ptr<PhysicalObject> element;
        const unsigned int spawnProb;
        
    public:
        SpawnEntry(std::shared_ptr<PhysicalObject> element, unsigned int spawnProb);
    };
    
    class SpawnArea: public Environment {
        std::vector<std::shared_ptr<SpawnEntry>> spawnEntries;
        
    public:
        SpawnArea(std::string name, std::string desc, SpawnEntry *);
        SpawnArea(std::string name, std::string desc, std::vector<std::shared_ptr<SpawnEntry>> spawnEntries);
        SpawnArea(const SpawnArea & env);
        SpawnArea(SpawnArea && env);
        virtual ~SpawnArea();
        
        void update();
    };
}

#endif
