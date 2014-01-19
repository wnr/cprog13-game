#include "Environment.h"
#include "Log.h"
#include "Constants.h"
#include "PhysicalObject.h"
#include "Entity.h"

using namespace game;

Environment::Environment(std::string name, std::string desc) : Environment("", name, desc) {}

Environment::Environment(std::string subType, std::string name, std::string desc) : BaseObject(OBJECT_TYPE_ENVIRONMENT, subType), name(name), description(desc) {}

Environment::Environment(const Environment & env) : BaseObject(env), name(env.name), description(env.description) {}

Environment::Environment(Environment && env) : BaseObject(env), name(env.name), description(env.description) {}

Environment::~Environment() {}

void Environment::setNeightbor(std::string direction, Environment * env) {
    std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
    neighbors[direction] = env;
}

Environment * Environment::getNeighbor(const std::string & direction) {
    if(neighbors.count(direction) == 0) {
        return NULL;
    }
    
    return neighbors[direction];
}

std::string Environment::getName() const {
    return name;
}

std::string Environment::getDescription() const {
    return description;
}

std::string Environment::getFullInfo() const {
    return getName() + ", " + getDescription();
}

std::vector<std::string> Environment::getDirections() const {
    std::vector<std::string> directions;
    for(auto entry : neighbors) {
        directions.push_back(entry.first);
    }
    
    return directions;
}

void Environment::update() {
    updateObjects();
}

void Environment::updateObjects() {
    for_each([](PhysicalObject * obj) {
        obj->update();
        return true;
    });
}

std::string Environment::toString() const {
    return "Environment";
}