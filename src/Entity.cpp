#include "Entity.h"

#include "Environment.h"
#include "Log.h"

using namespace game;

Entity::Entity(std::string type) : Entity(type, true) {}

Entity::Entity(std::string type, bool visible) : PhysicalObject(OBJECT_ENTITY_TYPE, type, visible), alive(true) {}

Entity::Entity(const Entity & entity) : PhysicalObject(entity), alive(entity.alive) {}

Entity::Entity(Entity && entity) : PhysicalObject(entity), alive(entity.alive) {} //TODO: Probably going to be copied now.

Entity::~Entity() {}

void Entity::setEnvironment(Environment * env) {
    this->env = env;
}

Environment * Entity::getEnvironment() const {
    return env;
}

bool Entity::move(const std::string &direction) {
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    log(this, "moved to " + direction);
    
    neighbor->addObject(env->removeObject(this));
    
    return true;
}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    log(this, "killed");
    alive = false;
}