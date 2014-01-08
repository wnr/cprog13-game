#include "Environment.h"

using namespace game;

Environment::Environment(std::string desc) : description(desc) {
    
}

Environment::Environment(const Environment & env) : description(env.description) {
    
}

Environment::Environment(Environment && env) : description(env.description) {
    
}

Environment::~Environment() {
    
}

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
    entities.push_back(std::weak_ptr<Entity>(entity));
}

void Environment::removeEntity(std::weak_ptr<Entity> entity) {
    std::remove_if(entities.begin(), entities.end(), [entity] (std::weak_ptr<Entity> ptr) -> bool {
        if(ptr.expired()) {
            return true;
        }
        
        if((ptr.lock()).get() == (entity.lock()).get()) {
            return true;
        }
        
        return false;
    });
}

void Environment::updateEntities() {
    for(auto entity : entities) {
        if(entity.expired()) {
            std::cerr << "Error: A pointer is gone.";
        } else {
            entity.lock()->update();
        }
    }
}