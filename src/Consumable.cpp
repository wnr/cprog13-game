#include "Consumable.h"

using namespace game;

Consumable::Consumable(std::string name, unsigned int potency, unsigned int weight) : Item(ITEM_TYPE_CONSUMABLE, weight, name), potency(potency) {}

Consumable::Consumable(const Consumable & consumable)   : Item(consumable), potency(consumable.potency) {}
Consumable::Consumable(Consumable && consumable)        : Item(consumable), potency(consumable.potency) {}

Consumable::~Consumable() {}

unsigned int Consumable::getPotency() const {
    return potency;
}

std::string Consumable::getStatisticalDescription() const {
    std::string desc = Item::getStatisticalDescription();
    desc += "\nPotency: " + std::to_string(potency);
    return desc;
}



