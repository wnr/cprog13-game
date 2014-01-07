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