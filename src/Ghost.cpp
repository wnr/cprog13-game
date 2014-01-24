#include "Ghost.h"
#include "Constants.h"
#include "Environment.h"

using namespace game;

Ghost::Ghost(Environment * env) : Ghost(env, CHARACTER_TYPE_GHOST, GHOST_HEALTH) {}
Ghost::Ghost(Environment * env, std::string subType, unsigned int maxHealth) : Ghost(env, subType, maxHealth, subType) {}
Ghost::Ghost(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Ghost(env, subType, maxHealth, name, GHOST_MOVE_PROB, GHOST_ATTACK_PROB) {}
Ghost::Ghost(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Ghost(env, subType, maxHealth, name, moveProb, attackProb, GHOST_BASE_ARMOR, GHOST_BASE_DODGE, GHOST_BASE_BLOCK, GHOST_BASE_MIN_DMG, GHOST_BASE_MAX_DMG, GHOST_BASE_CRIT_PROB, GHOST_BASE_CRIT_MOD) {}

Ghost::Ghost(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Monster(env, subType, maxHealth, name, moveProb, attackProb) {}

Ghost::Ghost(const Ghost & ghost)   : Monster(ghost) {}
Ghost::Ghost(Ghost && ghost)        : Monster(ghost) {}

Ghost::~Ghost() {}

void Ghost::kill() {
    Monster::kill();
    getEnvironment()->remove(this);
}

//std::string Ghost::getCompleteDescription() const {
//    return "Watch out, it's a scary " + getSubType() + " that might hurt you!\nHealth: " + std::to_string(getHealth());

void Ghost::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(50, "scared"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

Ghost::Attack Ghost::attack(const Character * attacker, const Attack & attack) {
    return Attack(0, "absorbed");
}

std::string Ghost::getPersonalDescription() const {
    return "It looks like a " + getName() + ". You don't believe in ghosts do ya?";
}

Ghost * Ghost::clone() const {
    Ghost * c = new Ghost(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}