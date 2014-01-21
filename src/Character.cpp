#include "Character.h"
#include "Constants.h"
#include "Backpack.h"
#include "Container.h"
#include "Environment.h"

using namespace game;

Character::Attack::Attack(unsigned int health) : Character::Attack::Attack(health, "") {}
Character::Attack::Attack(unsigned int health, std::string description) : health(health), description(description) {}

Character::Character(Environment * env, std::string subType, unsigned int maxHealth) : Character(env, subType, maxHealth, subType) {}
Character::Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Character(env, subType, maxHealth, name, CHARACTER_INVENTORY_SIZE) {}
Character::Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize) : PhysicalObject(OBJECT_TYPE_CHARACTER, subType, name), alive(true), env(env), inventory(new Backpack(inventorySize)), rottenness(0), maxHealth(maxHealth), health(maxHealth) {}

Character::Character(const Character & character)   : PhysicalObject(character), alive(character.alive), env(character.env), inventory(character.inventory), rottenness(character.rottenness), maxHealth(character.maxHealth), health(character.health) {}
Character::Character(Character && character)        : PhysicalObject(character), alive(character.alive), env(character.env), inventory(character.inventory), rottenness(character.rottenness), maxHealth(character.maxHealth), health(character.health) {}

Character::~Character() {}

Environment * Character::getEnvironment() const {
    return env;
}

Backpack * Character::getInventory() const {
    return inventory;
}

std::string Character::getName() const {
    if(!isAlive()) {
        return PhysicalObject::getName() + " corpse";
    }
    
    return PhysicalObject::getName();
}

bool Character::move(Environment * from, Environment * to) {
    env = to;
    to->push_back(from->remove(this));
    return true;
}

bool Character::move(const std::string &direction) {
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    move(env, neighbor);
    
    return true;
}

void Character::dropInventory() {
    inventory->for_each([this](Item * item){
        dropItem(item);
        return true;
    });
}

bool Character::pickItem(const Item * item) {
    return item->move(env, inventory);
}

bool Character::pickItem(const Item * item, Container * con) {
    return item->move(con, inventory);
}

bool Character::dropItem(const Item * item) {
    return item->move(inventory, env);
}

bool Character::putItem(const Item * item, Container * con) {
    return item->move(inventory, con);
}

bool Character::isAlive() const {
    return alive;
}

void Character::kill() {
    alive = false;
    setHealth(0);
}

unsigned int Character::getRottenness() const {
    return rottenness;
}

void Character::update() {
    PhysicalObject::update();
    
    if(!isAlive()) {
        if(++rottenness >= MAXIMUM_ROTTENNESS) {
            env->remove(this);
            return;
        }
    }
    
    inventory->update();
}

unsigned int Character::getMaxHealth() const {
    return maxHealth;
}

unsigned int Character::getHealth() const {
    return health;
}

void Character::setHealth(unsigned int health) {
    if(health > maxHealth) {
        throw std::invalid_argument("health must be set less than max health.");
    }
    
    this->health = health;
}

void Character::addHealth(int health) {
    int res = (int)this->health;
    res += health;
    
    if(res <= 0) {
        kill();
    } else if(res > maxHealth) {
        this->health = maxHealth;
    } else {
        setHealth(res);
    }
}

void Character::incHealth(unsigned int health) {
    addHealth(health);
}

void Character::decHealth(unsigned int health) {
    addHealth(-health);
}

Character::Attack Character::attack(const Character * attacker, unsigned int health) {
    return attack(attacker, Character::Attack(health));
}

Character::Attack Character::attack(const Character * attacker, unsigned int health, std::string description) {
    return attack(attacker, Character::Attack(health, description));
}

std::string Character::getPersonalDescription() const {
    return PhysicalObject::getPersonalDescription() + "A character of type " + getSubType();
}

std::string Character::getStatisticalDescription() const {
    std::string desc = "Health: " + unsignedValToString(getHealth()) + "/" + unsignedValToString(getMaxHealth());
    return desc;
}

