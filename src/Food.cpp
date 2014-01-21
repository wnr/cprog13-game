#include "Food.h"

using namespace game;

Food::Food() : Food(ITEM_TYPE_FOOD) {}

Food::Food(std::string name) : Food(name, FOOD_STRENGTH) {}

Food::Food(std::string name, unsigned int strength) : Food(name, strength, FOOD_WEIGHT) {}

Food::Food(std::string name, unsigned int strength, unsigned int weight) : Item(ITEM_TYPE_FOOD, weight, name), strength(strength) {}

Food::Food(const Food & food) : Item(food), strength(food.strength) {}

Food::Food(Food && food) : Item(food), strength(food.strength) {}

Food::~Food() {}

unsigned int Food::getStrength() const {
    return strength;
}