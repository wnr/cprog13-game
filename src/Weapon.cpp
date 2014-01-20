#include "Weapon.h"

#include "Constants.h"

using namespace game;

Weapon::Weapon(unsigned int dmg, unsigned int volume) : Weapon(ITEM_TYPE_WEAPON, dmg, volume) {}

Weapon::Weapon(std::string type, unsigned int dmg, unsigned int volume) : Weapon(type, dmg, dmg, 1, volume){}

Weapon::Weapon(std::string type, unsigned int minDmg, unsigned int maxDmg, float critModifier, unsigned int volume) : Weapon(type, true, minDmg, maxDmg, critModifier, volume) {}

Weapon::Weapon(std::string type, bool visible, unsigned int minDmg, unsigned int maxDmg, float critModifier, unsigned int volume) : BreakableItem(type, visible, volume), minDmg(minDmg), maxDmg(maxDmg), critModifier(critModifier) {}

Weapon::Weapon(const Weapon & weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::Weapon(Weapon && weapon) : BreakableItem(weapon), minDmg(weapon.minDmg), maxDmg(weapon.maxDmg), critModifier(weapon.critModifier) {}

Weapon::~Weapon() {}