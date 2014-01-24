#include "Troll.h"
#include "rand.h"
#include "Environment.h"

using namespace game;

Troll::Troll(Environment * env) : Troll(env, CHARACTER_TYPE_TROLL, TROLL_HEALTH) {}
Troll::Troll(Environment * env, std::string subType, unsigned int maxHealth) : Troll(env, subType, maxHealth, subType) {}
Troll::Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Troll(env, subType, maxHealth, name, TROLL_MOVE_PROB, TROLL_ATTACK_PROB) {}
Troll::Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Troll(env, subType, maxHealth, name, moveProb, attackProb, TROLL_BASE_ARMOR, TROLL_BASE_DODGE, TROLL_BASE_BLOCK, TROLL_BASE_MIN_DMG, TROLL_BASE_MAX_DMG, TROLL_BASE_CRIT_PROB, TROLL_BASE_CRIT_MOD) {}

Troll::Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Monster(env, subType, maxHealth, name, moveProb, attackProb) {}

Troll::Troll(const Troll & troll)   : Monster(troll) {}
Troll::Troll(Troll && troll)        : Monster(troll) {}

Troll::~Troll() {}

void Troll::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(getAttackPower(), "scratched"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

std::string Troll::getPersonalDescription() const {
    return "A ugly " + getName() + " who does not fancy your good looks. Watch out!";
}

Troll * Troll::clone() const {
    Troll * c = new Troll(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}