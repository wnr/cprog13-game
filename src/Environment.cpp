#include "Environment.h"
#include "Entity.h"
#include "Log.h"
#include "Constants.h"

using namespace game;

Environment::Environment(std::string desc) : description(desc) {}

Environment::Environment(const Environment & env) : description(env.description) {}

Environment::Environment(Environment && env) : description(env.description) {}

Environment::~Environment() {}

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
    push_back(std::move(entity));
}

std::unique_ptr<Entity> Environment::removeEntity(Entity * entity) {
    entity->setEnvironment(NULL);
    return remove(entity);
}

void Environment::update() {
    updateEntities();
}

void Environment::updateEntities() {
    for_each([this](Entity * entity) {
        entity->update(*this);
        return true;
    });
}

std::string Environment::toString() const {
    return "Environment";
}