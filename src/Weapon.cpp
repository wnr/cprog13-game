#include "Weapon.h"

#include "Constants.h"

using namespace game;

Weapon::Weapon(unsigned int dmg, unsigned int volume) : Weapon(ITEM_TYPE_WEAPON, dmg, volume) {}

Weapon::Weapon(std::string name, unsigned int dmg, unsigned int volume) : Weapon(name, dmg, dmg, 1, volume){}

Weapon::Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, float critModifier, unsigned int volume) : Weapon(name, true, minDmg, maxDmg, critModifier, volume) {}

Weapon::Weapon(std::string name, bool visible, unsigned int minDmg, unsigned int maxDmg, float critModifier, unsigned int volume) : BreakableItem(ITEM_TYPE_WEAPON, volume, name), minDmg(minDmg), maxDmg(maxDmg), critModifier(critModifier) {}

Weapon::Weapon(const Weapon & weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::Weapon(Weapon && weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::~Weapon() {}