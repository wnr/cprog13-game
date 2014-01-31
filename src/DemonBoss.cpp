#include "DemonBoss.h"
#include "rand.h"
#include "Constants.h" 

using namespace game;

DemonBoss::DemonBoss(Environment * env) : DemonBoss(env, CHARACTER_TYPE_BOSS, DEMON_BOSS_HEALTH) {}
DemonBoss::DemonBoss(Environment * env, std::string subType, unsigned int maxHealth) : DemonBoss(env, subType, maxHealth, DEMON_BOSS_NAME) {}
DemonBoss::DemonBoss(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : DemonBoss(env, subType, maxHealth, name, DEMON_BOSS_MOVE_PROB, DEMON_BOSS_ATTACK_PROB) {}
DemonBoss::DemonBoss(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : DemonBoss(env, subType, maxHealth, name, moveProb, attackProb, DEMON_BOSS_BASE_ARMOR, DEMON_BOSS_BASE_DODGE, DEMON_BOSS_BASE_BLOCK, DEMON_BOSS_BASE_MIN_DMG, DEMON_BOSS_BASE_MAX_DMG, DEMON_BOSS_BASE_CRIT_PROB, DEMON_BOSS_BASE_CRIT_MOD) {}

DemonBoss::DemonBoss(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Demon(env, subType, maxHealth, name, moveProb, attackProb, baseArmorRating, baseDodgeProb, baseBlockProb, baseMinDmg, baseMaxDmg, baseCritProb, baseCritMod) {}

DemonBoss::DemonBoss(const DemonBoss & DemonBoss)   : Demon(DemonBoss) {}
DemonBoss::DemonBoss(DemonBoss && DemonBoss)        : Demon(DemonBoss) {}

DemonBoss::~DemonBoss() {}

std::string DemonBoss::getPersonalDescription() const {
    return "The mighty " + getName() + "! He sees you as a meer fly but if you're not careful he might decide to squash the bug.";
}

std::string DemonBoss::getAttackType() const {
    return "soul crushed";
}

DemonBoss * DemonBoss::clone() const {
    DemonBoss * c = new DemonBoss(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}