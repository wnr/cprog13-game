#include "Entity.h"

#include "Environment.h"
#include "Constants.h"

using namespace game;

Entity::Entity(Engine * engine, std::string type) : engine(engine), type(type), alive(true) {
    LOG(type + ": Entity ctor");
}

Entity::Entity(const Entity & entity) : engine(entity.engine), type(entity.type), alive(entity.alive) {
    LOG(type + ": Entity ctor copy");
}

Entity::Entity(Entity && entity) : engine(entity.engine), type(entity.type), alive(entity.alive) {
    LOG(type + ": Entity ctor move");
}

Entity::~Entity() {
    LOG(type + ": Entity dtor");
    engine = NULL;
    alive = false;
    type.clear();
}

std::string Entity::getType() const {
    return type;
}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    LOG(type + ": Entity killed");
    alive = false;
}

void Entity::setEnvironment(Environment * env) {
    this->env = env;
}

bool Entity::move(const std::string &direction) {
    if(env == NULL) {
        LOG("ERROR: " + type + ": Entity does not have an Environment.");
        return false;
    }
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    LOG(type + ": Entity moving " + direction);
    
    neighbor->addEntity(env->removeEntity(this));
    
    return true;
}