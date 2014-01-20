#include "Character.h"
#include "Constants.h"

using namespace game;

Character::Attack::Attack(unsigned int health) : Character::Attack::Attack(health, "") {}

Character::Attack::Attack(unsigned int health, std::string description) : health(health), description(description) {}

Character::Character(Environment * env, std::string name, unsigned int maxHealth) : Character(env, name, maxHealth, ENTITY_TYPE_CHARACTER) {}

Character::Character(Environment * env, std::string name, unsigned int maxHealth, std::string subType) : Entity(env, subType, name), maxHealth(maxHealth), health(maxHealth) {
}

Character::Character(const Character & character) : Entity(character), maxHealth(character.maxHealth), health(character.health) {}

Character::Character(Character && character) : Entity(character), maxHealth(character.maxHealth), health(character.health) {}

Character::~Character() {}

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
        this->health = 0;
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

void Character::kill() {
    setHealth(0);
    Entity::kill();
}

std::string Character::getDescription() const {
    //TODO Discuss alternatives
    
    if(!isAlive()) {
        return getName() + " corpse";
    }
    
    return getName();
}

Character::Attack Character::attack(const Character * attacker, unsigned int health) {
    return attack(attacker, Character::Attack(health));
}

Character::Attack Character::attack(const Character * attacker, unsigned int health, std::string description) {
    return attack(attacker, Character::Attack(health, description));
}