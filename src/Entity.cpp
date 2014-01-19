#include "Entity.h"

#include "Environment.h"
#include "Constants.h"
#include "Backpack.h"
#include "Container.h"

using namespace game;

Entity::Entity(Environment * env, std::string type) : Entity(env, type, true, ENTITY_INVENTORY_SIZE) {}

Entity::Entity(Environment * env, std::string type, bool visible, int inventorySize) : PhysicalObject(OBJECT_TYPE_ENTITY, type, visible), alive(true), env(env), inventory(new Backpack(inventorySize)), rottenness(0) {
}

Entity::Entity(const Entity & entity) : PhysicalObject(entity), alive(entity.alive), env(entity.env) {}

Entity::Entity(Entity && entity) : PhysicalObject(entity), alive(entity.alive), env(entity.env) {}

Entity::~Entity() {}

Environment * Entity::getEnvironment() const {
    return env;
}

Backpack * Entity::getInventory() const {
    return inventory;
}

bool Entity::move(Environment * from, Environment * to) {
    env = to;
    to->push_back(from->remove(this));
    return true;
}

bool Entity::move(const std::string &direction) {
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    move(env, neighbor);
    
    return true;
}

void Entity::dropInventory() {
    inventory->for_each([this](Item * item){
        dropItem(item);
        return true;
    });
}

bool Entity::pickItem(const Item * item) {
    return item->move(env, inventory);
}

bool Entity::pickItem(const Item * item, Container * con) {
    return item->move(con, inventory);
}

bool Entity::dropItem(const Item * item) {
    return item->move(inventory, env);
}

bool Entity::putItem(const Item * item, Container * con) {
    return item->move(inventory, con);
}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    alive = false;
}

unsigned int Entity::getRottenness() const {
    return rottenness;
}

void Entity::update() {
    PhysicalObject::update();
    
    if(!isAlive()) {
        if(++rottenness >= MAXIMUM_ROTTENNESS) {
            env->remove(this);
        }
    }
    
    inventory->update();
}