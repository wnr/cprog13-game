#include "Character.h"
#include "Constants.h"
#include "Log.h"

using namespace game;

Character::Character(Environment * env, std::string name, unsigned int maxHealth) : Character(env, name, maxHealth, ENTITY_TYPE_CHARACTER) {}

Character::Character(Environment * env, std::string name, unsigned int maxHealth, std::string type) : Entity(env, type), maxHealth(maxHealth), health(maxHealth), name(name) {
}

Character::Character(const Character & character) : Entity(character), maxHealth(character.maxHealth), health(character.health), name(character.name) {}

Character::Character(Character && character) : Entity(character), maxHealth(character.maxHealth), health(character.health), name(character.name) {}

Character::~Character() {}

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
    
    if(res <= 0) {
        log(this, "health decreased 0 or below. Killing character.");
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
    setHealth(0);
    Entity::kill();
}

std::string Character::getDescription() const {
    return name; //TODO Discuss alternatives
}