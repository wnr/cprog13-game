#include "Entity.h"

#include "Environment.h"
#include "Log.h"

using namespace game;

Entity::Entity(std::string type) : Entity(type, true) {}

Entity::Entity(std::string type, bool visible) : Object(type, visible, false), alive(true) {}

Entity::Entity(const Entity & entity) : Object(entity), alive(entity.alive) {}

Entity::Entity(Entity && entity) : Object(entity), alive(entity.alive) {} //TODO: Probably going to be copied now.

Entity::~Entity() {}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    log(this, "killed");
    alive = false;
}

void Entity::setEnvironment(Environment * env) {
    this->env = env;
}

bool Entity::move(const std::string &direction) {
    if(env == NULL) {
        error(this, "Entity does not have an Environment.");
        return false;
    }
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    log(this, "move " + direction);
    
    neighbor->addEntity(env->removeEntity(this));
    
    return true;
}

std::string Entity::toString() const {
    return "Entity(" + type + ")";
}