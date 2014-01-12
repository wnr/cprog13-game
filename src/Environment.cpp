#include "Environment.h"
#include "Entity.h"
#include "Log.h"
#include "Constants.h"

using namespace game;

Environment::Environment(std::string desc) : description(desc) {
    log(this, "ctor");
}

Environment::Environment(const Environment & env) : description(env.description) {
    log(this, "ctor copy");
}

Environment::Environment(Environment && env) : description(env.description) {
    log(this, "ctor move");
}

Environment::~Environment() {
    log(this, "dtor");
}

void Environment::setNeightbor(std::string direction, Environment * env) {
    neighbors[direction] = env;
}

Environment * Environment::getNeighbor(const std::string & direction) {
    if(neighbors.count(direction) == 0) {
        return NULL;
    }
    
    return neighbors[direction];
}

std::string Environment::getDescription() const {
    return description;
}

std::vector<std::string> Environment::getDirections() const {
    std::vector<std::string> directions;
    for(auto entry : neighbors) {
        directions.push_back(entry.first);
    }
    
    return directions;
}

void Environment::addEntity(std::unique_ptr<Entity> entity) {
    entity->setEnvironment(this);
    entities.push_back(std::move(entity));
}

std::unique_ptr<Entity> Environment::removeEntity(Entity * entity) {
    std::unique_ptr<Entity> removed;
    
    auto it = std::remove_if(entities.begin(), entities.end(), [entity, &removed] (std::unique_ptr<Entity> & ptr) -> bool {
        //TODO: Can equality be checked like this? If the pointers are pointing to the same address they should be the same...
        if(ptr.get() == entity) {
            removed = std::move(ptr);
            return true;
        }
        
        return false;
    });
    
    entities.erase(it, entities.end());
    
    return removed;
}

void Environment::update() {
    updateEntities();
}

void Environment::updateEntities() {
    for(auto & entity : entities) {
        entity->update(*this);
    }
}

std::string Environment::toString() const {
    return "Environment";
}

std::vector<const Entity*> Environment::getEntities(bool includePlayer) const {
    std::vector<const Entity*> result;
    
    for(auto & entity : entities) {
        if(entity->getType() == ENTITY_PLAYER_TYPE && !includePlayer) {
            continue;
        }
        
        result.push_back(entity.get());
    }
    
    return result;
}