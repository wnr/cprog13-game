#include "Entity.h"

#include "Environment.h"
#include "Log.h"

using namespace game;

Entity::Entity(std::string type) : Entity(type, true) {}

Entity::Entity(std::string type, bool visible) : Object(type, visible), alive(true) {}

Entity::Entity(const Entity & entity) : Object(entity), alive(entity.alive) {}

Entity::Entity(Entity && entity) : Object(entity), alive(entity.alive) {} //TODO: Probably going to be copied now.

Entity::~Entity() {}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    log(this, "killed");
    alive = false;
}

std::string Entity::toString() const {
    return "Entity(" + getType() + ")";
}