#include "Potion.h"
#include "Character.h"
#include "Backpack.h"

using namespace game;

Potion::Potion(std::string name) : Potion(name, POTION_POTENCY) {}

Potion::Potion(std::string name, unsigned int potency) : Potion(name, potency, POTEION_WEIGHT) {}

Potion::Potion(std::string name, unsigned int potency, unsigned int weight) : Consumable(name, potency, weight) {}

Potion::Potion(const Potion & potion) : Consumable(potion) {}

Potion::Potion(Potion && potion) : Consumable(potion) {}

Potion::~Potion() {}

std::string Potion::consume(Character * character) const {
    unsigned int before = character->getMaxHealth();
    addMaxHealth(getPotency(), character);
    unsigned int diff = character->getMaxHealth() - before;
    
    if(character->getInventory()->remove(this) == nullptr){
        throw std::runtime_error(character->getName() + " consumed " + getName() + " that is not in the inventory");
    }
    
    return "increased max HP by " + std::to_string(diff) + " points!";
}

void Potion::addMaxHealth(int amount, Character * character) const {
    character->addMaxHealth(amount);
}

