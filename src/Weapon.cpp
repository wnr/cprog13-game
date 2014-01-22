#include "Weapon.h"
#include "rand.h"

#include "Constants.h"

using namespace game;

Weapon::Weapon(unsigned int dmg, unsigned int weight) : Weapon(ITEM_TYPE_WEAPON, dmg, weight) {}

Weapon::Weapon(std::string name, unsigned int dmg, unsigned int weight) : Weapon(name, dmg, dmg, weight){}

Weapon::Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int weight) : Weapon(name, minDmg, maxDmg, WEAPON_CRIT_PROB, WEAPON_CRIT_MOD, weight) {}

Weapon::Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int critProb, float critModifier, unsigned int weight) : BreakableItem(ITEM_TYPE_WEAPON, weight, name), minDmg(minDmg), maxDmg(maxDmg), critProb(critProb), critModifier(critModifier) {
    if(!isWeapon()){
        throw new std::invalid_argument("The subType: " +  getSubType() + " is not allowed.");
    }
}

Weapon::Weapon(const Weapon & weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critProb(weapon.critProb), critModifier(weapon.critModifier) {}

Weapon::Weapon(Weapon && weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critProb(weapon.critProb), critModifier(weapon.critModifier) {}

Weapon::~Weapon() {}

int Weapon::getMinDmg() const {
    return minDmg;
}

int Weapon::getMaxDmg() const {
    return maxDmg;
}

int Weapon::getCritProb() const {
    return critProb;
}

float Weapon::getCritModifier() const {
    return critModifier;
}

std::string Weapon::getStatisticalDescription() const {
    std::string desc = BreakableItem::getStatisticalDescription();
    desc += "\nDmg: " + unsignedValToString(getMinDmg()) + "-" + unsignedValToString(getMaxDmg());
    desc += "\nCrit prob: " + unsignedValToString(getCritProb());
    desc += "\nCrit mod: " + unsignedValToString(getCritModifier());
    return desc;
}

unsigned int Weapon::getAttackPower() const {
    if(isWorking()) {
        return rand(getMinDmg(), getMaxDmg(), true);
    } else {
        return 0;
    }
}