#include "Vampire.h"
#include "Constants.h"
#include "Environment.h"
#include "Character.h"

using namespace game;

Vampire::Vampire(Environment * env) : Vampire(env, CHARACTER_TYPE_VAMPIRE, VAMPIRE_HEALTH) {}
Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth) : Vampire(env, subType, maxHealth, subType) {}
Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Vampire(env, subType, maxHealth, name, VAMPIRE_MOVE_PROB, VAMPIRE_ATTACK_PROB) {}
Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Vampire(env, subType, maxHealth, name, moveProb, attackProb, VAMPIRE_BASE_ARMOR, VAMPIRE_BASE_DODGE, VAMPIRE_BASE_BLOCK, VAMPIRE_BASE_MIN_DMG, VAMPIRE_BASE_MAX_DMG, VAMPIRE_BASE_CRIT_PROB, VAMPIRE_BASE_CRIT_MOD) {}

Vampire::Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Monster(env, subType, maxHealth, name, moveProb, attackProb, baseArmorRating, baseDodgeProb, baseBlockProb, baseMinDmg, baseMaxDmg, baseCritProb, baseCritMod) {}

Vampire::Vampire(const Vampire & vampire)   : Monster(vampire) {}
Vampire::Vampire(Vampire && vampire)        : Monster(vampire) {}

Vampire::~Vampire() {}

std::string Vampire::getPersonalDescription() const {
    return "Dracula´s gonna fuck you up!";
}

Vampire * Vampire::clone() const {
    Vampire * c = new Vampire(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}

Vampire::Attack Vampire::performAttack(Character * defender, std::string attackType) {
    Attack result = Monster::performAttack(defender,attackType);
    if(result.health > 0) {
        unsigned int before = getHealth();
        unsigned int stolenHealth = result.health/10;
        if (stolenHealth < 1) {stolenHealth = 1;}
        incHealth(stolenHealth);
        unsigned int healthChange =  getHealth() - before;
        if(healthChange > 0 && defender->getSubType() == CHARACTER_TYPE_PLAYER) {
            std::cout << getName() << " life stole " << healthChange << " HP.";
        }
    }
    return result;
}

std::string Vampire::getAttackType() const {
    return "bitten";
}