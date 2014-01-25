#include "Food.h"
#include "Consumable.h"
#include "Character.h"
#include "Inventory.h"

using namespace game;

Food::Food(std::string name) : Food(name, FOOD_POTENCY) {}

Food::Food(std::string name, unsigned int potency) : Food(name, potency, FOOD_WEIGHT) {}

Food::Food(std::string name, unsigned int potency, unsigned int weight) : Consumable(name, potency, weight) {}

Food::Food(const Food & food)   : Consumable(food) {}
Food::Food(Food && food)        : Consumable(food) {}

Food::~Food() {}

std::string Food::consume(Character * character) const {
    unsigned int before = character->getHealth();
    incHealth(getPotency(), character);
    unsigned int diff = character->getHealth() - before;
    
    if(character->getInventory()->remove(this) == nullptr){
        throw std::runtime_error(character->getName() + " consumed " + getName() + " that is not in the inventory");
    }
    
    return "healed " + std::to_string(diff) + " HP!";
}

void Food::incHealth(unsigned int amount, Character * character) const {
    character->incHealth(amount);
}

Food * Food::clone() const {
    Food * c = new Food(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}

    
