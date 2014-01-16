#include "Entity.h"

#include "Environment.h"
#include "Log.h"
#include "Constants.h"

using namespace game;

Entity::Entity(Environment * env, std::string type) : Entity(env, type, true) {}

Entity::Entity(Environment * env, std::string type, bool visible) : PhysicalObject(OBJECT_ENTITY_TYPE, type, visible), alive(true), env(env) {}

Entity::Entity(const Entity & entity) : PhysicalObject(entity), alive(entity.alive), env(entity.env) {}

Entity::Entity(Entity && entity) : PhysicalObject(entity), alive(entity.alive), env(entity.env) {}

Entity::~Entity() {}

Environment * Entity::getEnvironment() const {
    return env;
}

void Entity::move(Environment * from, Environment * to) {
    env = to;
    
    PhysicalObject::move(from, to);
}

bool Entity::move(const std::string &direction) {
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    move(env, neighbor);
    
    return true;
}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    log(this, "killed");
    alive = false;
}