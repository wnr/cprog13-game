#include "Environment.h"

#include <iterator>

#include "Constants.h"
#include "PhysicalObject.h"
#include "Character.h"
#include "rand.h"


using namespace game;

Environment::Environment(std::string name, std::string desc) : Environment("", name, desc) {}

Environment::Environment(std::string subType, std::string name, std::string desc) : BaseObject(OBJECT_TYPE_ENVIRONMENT, subType, name), description(desc) {}

Environment::Environment(const Environment & env)   : BaseObject(env), GameStorage(env), description(env.description), neighbors(env.neighbors) {}
Environment::Environment(Environment && env)        : BaseObject(env), GameStorage(env), description(env.description), neighbors(env.neighbors) {}

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

Environment * Environment::randomNeighbor() const {
    if(neighbors.empty()) {
        return NULL;
    }
    
    unsigned int picked = rand((unsigned int)neighbors.size());
    
    auto env = std::next(neighbors.begin(), picked);
    
    return env->second;
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
    BaseObject::update();
}

void Environment::updateObjects() {
    bool tickSync = getTickSync();
    
    for_each([tickSync](PhysicalObject * obj) {
        if(tickSync == obj->getTickSync()) {
            obj->update();
        }
    });
}

std::string Environment::toString() const {
    return "Environment";
}