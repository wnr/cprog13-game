#include "Environment.h"
#include "Log.h"
#include "Constants.h"
#include "Object.h"

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

void Environment::addObject(std::unique_ptr<Object> obj) {
    obj->setEnvironment(this);
    push_back(std::move(obj));
}

std::unique_ptr<Object> Environment::removeObject(Object * obj) {
    obj->setEnvironment(NULL);
    return remove(obj);
}

void Environment::update() {
    updateObjects();
}

void Environment::updateObjects() {
    for_each([this](Object * obj) {
        obj->update(*this);
        return true;
    });
}

std::string Environment::toString() const {
    return "Environment";
}