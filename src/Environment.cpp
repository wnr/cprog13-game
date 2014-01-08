#include "Environment.h"

#include "Entity.h"

using namespace game;

Environment::Environment(std::string desc) : description(desc) {}

Environment::Environment(const Environment & env) : description(env.description) {}

Environment::Environment(Environment && env) : description(env.description) {}

Environment::~Environment() {}

void Environment::setNeightbor(std::string direction, std::weak_ptr<Environment> env) {
    neighbors[direction] = env;
}

std::weak_ptr<Environment> Environment::getNeighbor(const std::string & direction) {
    if(neighbors.count(direction) == 0) {
        return std::weak_ptr<Environment>();
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

void Environment::addEntity(std::weak_ptr<Entity> entity) {
    entities.push_back(entity);
    entity.lock()->setEnvironment(this);
}

std::weak_ptr<Entity> Environment::removeEntity(const Entity * entity) {
    std::weak_ptr<Entity> removed;
    
    std::remove_if(entities.begin(), entities.end(), [entity, &removed] (std::weak_ptr<Entity> ptr) -> bool {
        if(ptr.expired()) {
            return true;
        }
        
        if((ptr.lock()).get() == entity) {
            removed = ptr;
            return true;
        }
        
        return false;
    });
    
    return removed;
}

void Environment::removeEntity(std::weak_ptr<Entity> entity) {
    removeEntity(entity.lock().get());
}


void Environment::update() {
    updateEntities();
}

void Environment::updateEntities() {
    for(auto entity : entities) {
        if(entity.expired()) {
            std::cerr << "Error: A pointer is gone.";
        } else {
            entity.lock()->update(*this);
        }
    }
}