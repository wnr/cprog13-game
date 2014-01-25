#include "Vampire.h"
#include "Constants.h"
#include "Environment.h"
#include "Character.h"

using namespace game;

Vampire::Vampire(Environment * env) : Vampire(env, CHARACTER_TYPE_VAMPIRE, VAMPIRE_HEALTH) {}
Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth) : Vampire(env, subType, maxHealth, subType) {}
Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Vampire(env, subType, maxHealth, name, VAMPIRE_MOVE_PROB, VAMPIRE_ATTACK_PROB) {}
Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Vampire(env, subType, maxHealth, name, moveProb, attackProb, VAMPIRE_BASE_ARMOR, VAMPIRE_BASE_DODGE, VAMPIRE_BASE_BLOCK, VAMPIRE_BASE_MIN_DMG, VAMPIRE_BASE_MAX_DMG, VAMPIRE_BASE_CRIT_PROB, VAMPIRE_BASE_CRIT_MOD) {}

Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Monster(env, subType, maxHealth, name, moveProb, attackProb) {}

Vampire::Vampire(const Vampire & vampire)   : Monster(vampire) {}
Vampire::Vampire(Vampire && vampire)        : Monster(vampire) {}

Vampire::~Vampire() {}

void Vampire::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(50, "scared"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

Vampire::Attack Vampire::attack(const Character * attacker, const Attack & attack) {
    return Attack(0, "absorbed");
}

std::string Vampire::getPersonalDescription() const {
    return "It looks like a " + getName() + ". You don't believe in Vampires do ya?";
}

Vampire * Vampire::clone() const {
    Vampire * c = new Vampire(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}