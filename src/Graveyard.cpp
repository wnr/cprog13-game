#include "Graveyard.h"
#include "Constants.h"
#include "rand.h"
#include "Ghost.h"

using namespace game;

Graveyard::Graveyard(std::string name, std::string desc, unsigned int ghostSpawnProb) : Environment(OBJECT_TYPE_GRAVEYARD_ENVIRONMENT, name, desc), ghostSpawnProb(ghostSpawnProb) {}

Graveyard::Graveyard(const Graveyard & env) : Environment(env), ghostSpawnProb(env.ghostSpawnProb) {}

Graveyard::Graveyard(Graveyard && env) : Environment(env), ghostSpawnProb(env.ghostSpawnProb) {}

Graveyard::~Graveyard() {}

void Graveyard::update() {
    if(happen(ghostSpawnProb)) {
        push_back(std::unique_ptr<PhysicalObject>(new Ghost(this)));
    }
    
    Environment::update();
}