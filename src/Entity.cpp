#include "Entity.h"

using namespace game;

Entity::Entity(Engine * engine, std::string type) : engine(engine), type(type), alive(true) {}

Entity::Entity(const Entity & entity) : engine(entity.engine), type(entity.type), alive(entity.alive) {}

Entity::Entity(Entity && entity) : engine(entity.engine), type(entity.type), alive(entity.alive) {}

Entity::~Entity() {
    engine = NULL;
    alive = false;
    type.clear();
}

std::string Entity::getType() const {
    return type;
}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    alive = false;
}