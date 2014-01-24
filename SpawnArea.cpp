#include "SpawnArea.h"
#include "Constants.h"
#include "rand.h"
#include "Ghost.h"
#include <vector>

using namespace game;

SpawnEntry::SpawnEntry(std::shared_ptr<PhysicalObject> element, unsigned int spawnProb) : element(element), spawnProb(spawnProb) {}

SpawnArea::SpawnArea(std::string name, std::string desc, SpawnEntry * spawnEntry) : SpawnArea(name, desc, {std::shared_ptr<SpawnEntry>(spawnEntry)}) {}

SpawnArea::SpawnArea(std::string name, std::string desc, std::vector<std::shared_ptr<SpawnEntry>> spawnEntries) : Environment(ENVIRONMENT_TYPE_SPAWNER, name, desc), spawnEntries(spawnEntries) {}

SpawnArea::SpawnArea(const SpawnArea & env) : Environment(env), spawnEntries(env.spawnEntries) {}

SpawnArea::SpawnArea(SpawnArea && env) : Environment(env), spawnEntries(env.spawnEntries) {}

SpawnArea::~SpawnArea() {}

void SpawnArea::update() {
//    for(std::shared_ptr<SpawnEntry> spawnEntry: spawnEntries){
//        if(happen(spawnEntry->spawnProb)) {
//            
//            std::unique_ptr<PhysicalObject> clone(spawnEntry->element->clone());
//            if(typeid(*clone) != typeid(*spawnEntry->element)){
//                // Sanity check
//                throw std::runtime_error("Clone is not the same type as element, prob missing the clone() function somewehere.");
//            } else {
//                push_back(std::move(clone));
//            }
//            
//        }
//    }
}