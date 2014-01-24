#include "Demon.h"
#include "rand.h"
#include "Constants.h" 

using namespace game;

Demon::Demon(Environment * env) : Demon(env, CHARACTER_TYPE_DEMON, DEMON_HEALTH) {}
Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth) : Demon(env, subType, maxHealth, subType) {}
Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Demon(env, subType, maxHealth, name, DEMON_MOVE_PROB, DEMON_ATTACK_PROB) {}
Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Demon(env, subType, maxHealth, name, moveProb, attackProb, DEMON_BASE_ARMOR, DEMON_BASE_DODGE, DEMON_BASE_BLOCK, DEMON_BASE_MIN_DMG, DEMON_BASE_MAX_DMG, DEMON_BASE_CRIT_PROB, DEMON_BASE_CRIT_MOD) {}

Demon::Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Monster(env, subType, maxHealth, name, moveProb, attackProb) {}
Demon::Demon(const Demon & demon)   : Monster(demon) {}
Demon::Demon(Demon && demon)        : Monster(demon) {}

Demon::~Demon() {}

void Demon::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(6666, "soul eaten"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

Demon::Attack Demon::attack(const Character * attacker, const Attack & attack) {
    static const unsigned int dodgeProb = 25;
    static const float reduction = 0.8f;
    
    Attack actual((1.0f - reduction) * attack.health);
    
    if(happen(dodgeProb)) {
        actual.health = 0;
    }
    
    decHealth(actual.health);
    
    if(actual.health == 0) {
        actual.description = "laughed at";
    }
    
    return actual;
}

std::string Demon::getPersonalDescription() const {
    return "A powerful " + getName() + " from the world below. Gear up!";
}

Demon * Demon::clone() const {
    Demon * c = new Demon(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}