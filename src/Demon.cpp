#include "Demon.h"
#include "rand.h"
#include "Constants.h" 

using namespace game;

Demon::Demon(Environment * env) : Demon(env, CHARACTER_TYPE_DEMON, DEMON_HEALTH) {}
Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth) : Demon(env, subType, maxHealth, subType) {}
Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Demon(env, subType, maxHealth, name, DEMON_MOVE_PROB, DEMON_ATTACK_PROB) {}
Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Demon(env, subType, maxHealth, name, moveProb, attackProb, DEMON_BASE_ARMOR, DEMON_BASE_DODGE, DEMON_BASE_BLOCK, DEMON_BASE_MIN_DMG, DEMON_BASE_MAX_DMG, DEMON_BASE_CRIT_PROB, DEMON_BASE_CRIT_MOD) {}

Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Monster(env, subType, maxHealth, name, moveProb, attackProb, baseArmorRating, baseDodgeProb, baseBlockProb, baseMinDmg, baseMaxDmg, baseCritProb, baseCritMod) {}

Demon::Demon(const Demon & demon)   : Monster(demon) {}
Demon::Demon(Demon && demon)        : Monster(demon) {}

Demon::~Demon() {}

Demon::Attack Demon::attack(Character * attacker, const Attack & attack) {
    Attack result = Monster::attack(attacker, attack);
    if(result.health == 0) {
        result.type = "laughed at";
    }
    return result;
}

std::string Demon::getPersonalDescription() const {
    return "A powerful " + getName() + " from the world below. Gear up!";
}

std::string Demon::getAttackType() const {
    return "soul eaten";
}

Demon * Demon::clone() const {
    Demon * c = new Demon(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}
