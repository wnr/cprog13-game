#include "Entity.h"

#include "Environment.h"

using namespace game;

Entity::Entity(Engine * engine, std::string type) : engine(engine), type(type), alive(true) {}

Entity::Entity(const Entity & entity) : engine(entity.engine), type(entity.type), alive(entity.alive) {}

Entity::Entity(Entity && entity) : engine(entity.engine), type(entity.type), alive(entity.alive) {}

Entity::~Entity() {
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
    alive = false;
}

void Entity::setEnvironment(Environment * env) {
    this->env = env;
}

bool Entity::move(const std::string &direction) {
    if(env == NULL) {
        std::cerr << "Entity does not have an Environment.";
        return false;
    }
    
    std::weak_ptr<Environment> neighbor = env->getNeighbor(direction);
    
    if(neighbor.expired()) {
        return false;
    }
    
    std::shared_ptr<Environment> newEnv = neighbor.lock();
    
    newEnv->addEntity(env->removeEntity(this));
    env = newEnv.get();
    
    return true;
}