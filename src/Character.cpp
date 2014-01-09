#include "Character.h"
#include "Constants.h"
#include "Log.h"

using namespace game;

Character::Character(Engine * engine, std::string name, int maxHealth) : Character(engine, name, maxHealth, ENTITY_CHARACTER_TYPE) {}
Character::Character(Engine * engine, std::string name, int maxHealth, std::string type) : Entity(engine, type), maxHealth(maxHealth), health(maxHealth), name(name) {
    log(this, "ctor");
}

Character::Character(const Character & character) : Entity(character), maxHealth(character.maxHealth), health(character.health), name(character.name) {
    log(this, "ctor copy");
}

Character::Character(Character && character) : Entity(character), maxHealth(character.maxHealth), health(character.health), name(character.name) {
    log(this, "ctor move");
}

Character::~Character() {
    log(this, "dtor");
}

std::string Character::getName() const {
    return name;
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
    
    log(this, "health set to " + std::to_string(this->health));
}

void Character::addHealth(int health) {
    int res = (int)this->health;
    res += health;
    
    if(res < 0) {
        log(this, "health decreased below 0. Killing character.");
        this->health = 0;
        kill();
    } else if(res > maxHealth) {
        this->health = maxHealth;
        log(this, "health increased above max. Set to max.");
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

void Character::kill() {
    log(this, "killed");
    setHealth(0);
    Entity::kill();
}

std::string Character::toString() const {
    return Entity::toString() + ":" + "Character(" + name + ")";
}

std::string Character::getDescription() const {
    return name;
}