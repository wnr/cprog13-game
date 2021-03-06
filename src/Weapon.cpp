#include "Weapon.h"
#include "rand.h"

#include "Constants.h"

using namespace game;

Weapon::Weapon(unsigned int dmg, unsigned int weight) : Weapon(ITEM_TYPE_WEAPON, dmg, weight) {}

Weapon::Weapon(std::string name, unsigned int dmg, unsigned int weight) : Weapon(name, dmg, dmg, weight){}

Weapon::Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int weight) : Weapon(name, minDmg, maxDmg, weight, WEAPON_CRIT_PROB, WEAPON_CRIT_MOD) {}

Weapon::Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int weight, unsigned int critProb, unsigned int critModifier) : BreakableItem(ITEM_TYPE_WEAPON, weight, name), minDmg(minDmg), maxDmg(maxDmg), critProb(critProb), critModifier(critModifier) {
    if(!isWeapon()){
        throw new std::invalid_argument("The subType: " +  getSubType() + " is not allowed.");
    }
}

Weapon::Weapon(const Weapon & weapon)   : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critProb(weapon.critProb), critModifier(weapon.critModifier) {}
Weapon::Weapon(Weapon && weapon)        : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critProb(weapon.critProb), critModifier(weapon.critModifier) {}

Weapon::~Weapon() {}

unsigned int Weapon::getMinDmg() const {
    return minDmg;
}

unsigned int Weapon::getMaxDmg() const {
    return maxDmg;
}

unsigned int Weapon::getCritProb() const {
    return critProb;
}

unsigned int Weapon::getCritModifier() const {
    return critModifier;
}

bool Weapon::affectDurability(unsigned int power) {
    if(!isWorking() || power < getMinDmg()) {
        return false;
    } else {
        if(happen(5)){
            decDurability(1);
        }
        return !isWorking();
    }
}

std::string Weapon::getStatisticalDescription() const {
    std::string desc = BreakableItem::getStatisticalDescription();
    desc += "\nDmg: " + unsignedValToString(getMinDmg()) + "-" + unsignedValToString(getMaxDmg());
    desc += "\nCrit prob: " + unsignedValToString(getCritProb());
    desc += "\nCrit mod: " + unsignedValToString(getCritModifier());
    return desc;
}

Weapon * Weapon::clone() const {
    Weapon * c = new Weapon(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}