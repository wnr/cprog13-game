#include "Entity.h"

#include "Environment.h"
#include "Log.h"

using namespace game;

Entity::Entity(Engine * engine, std::string type) : Entity(engine, type, true) {
    log(this, "ctor");
}

Entity::Entity(Engine * engine, std::string type, bool visible) : Object(engine, type, visible, false), alive(true) {
    log(this, "ctor");
}

Entity::Entity(const Entity & entity) : Object(entity), alive(entity.alive) {
    log(this, "ctor copy");
}

Entity::Entity(Entity && entity) : Object(entity), alive(entity.alive) {
    log(this, "ctor move");
}

Entity::~Entity() {
    log(this, "dtor");
    engine = NULL;
    alive = false;
    type.clear();
}

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