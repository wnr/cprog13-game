#include "Weapon.h"

#include "Log.h"
#include "Constants.h"

using namespace game;

Weapon::Weapon(int dmg) : Weapon(ITEM_WEAPON_TYPE, dmg, dmg, 1){}

Weapon::Weapon(std::string type, int minDmg, int maxDmg, float critModifier) : Weapon(type, true, true, true, minDmg, maxDmg, critModifier) {}

Weapon::Weapon(std::string type, bool visible, bool breakable, bool working, int minDmg, int maxDmg, float critModifier) : Item(type, visible, breakable, working), minDmg(minDmg), maxDmg(maxDmg), critModifier(critModifier) {}

Weapon::Weapon(const Weapon & weapon) : Item(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::Weapon(Weapon && weapon) : Item(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::~Weapon() {}

std::string Weapon::toString() const {
    return "Weapon(" + getType() + ")";
}