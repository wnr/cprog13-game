#include "Weapon.h"

#include "Log.h"
#include "Constants.h"

using namespace game;

Weapon::Weapon(int dmg) : Weapon(ITEM_WEAPON_TYPE, dmg) {}

Weapon::Weapon(std::string type, int dmg) : Weapon(type, dmg, dmg, 1){}

Weapon::Weapon(std::string type, int minDmg, int maxDmg, float critModifier) : Weapon(type, true, minDmg, maxDmg, critModifier) {}

Weapon::Weapon(std::string type, bool visible, int minDmg, int maxDmg, float critModifier) : BreakableItem(type, visible), minDmg(minDmg), maxDmg(maxDmg), critModifier(critModifier) {}

Weapon::Weapon(const Weapon & weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::Weapon(Weapon && weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::~Weapon() {}

std::string Weapon::toString() const {
    return "Weapon(" + getType() + ")";
}