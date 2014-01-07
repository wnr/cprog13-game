#include "Environment.h"

using namespace game;
using std::string;
using std::map;
using std::weak_ptr;

Environment::Environment(string desc) : description(desc) {
    
}

Environment::Environment(const Environment & env) : description(env.description) {
    
}

Environment::Environment(Environment && env) : description(env.description) {
    
}

Environment::~Environment() {
    
}

void Environment::setNeightbor(string direction, weak_ptr<Environment> env) {
    neighbors[direction] = env;
}

weak_ptr<Environment> Environment::getNeighbor(const std::string & direction) {
    if(neighbors.count(direction) == 0) {
        throw std::invalid_argument("No environment found in that direction.");
    }
    
    return neighbors[direction];
}

std::string Environment::getDescription() const {
    return description;
}