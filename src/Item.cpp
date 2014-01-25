#include "Item.h"

using namespace game;

Item::Item(std::string subType, unsigned int weight) : Item(subType, weight, subType) {}

Item::Item(std::string subType, unsigned int weight, std::string name) : PhysicalObject(OBJECT_TYPE_ITEM, subType, name), weight(weight){}

Item::Item(const Item & item)   : PhysicalObject(item), weight(item.weight) {}
Item::Item(Item && item)        : PhysicalObject(item), weight(item.weight) {}

Item::~Item() {}

unsigned int Item::getWeight() const {
    return weight;
}

void Item::update() {
    PhysicalObject::update();
}

int operator+=(int & value, const Item & item) {
    return value += item.getWeight();
}

int operator+(const Item & item1, const Item & item2) {
    return item1.getWeight() + item2.getWeight();
}

bool operator<(int value, const game::Item & item) {
    return value < item.getWeight();
}

std::string Item::getPersonalDescription() const {
    return PhysicalObject::getPersonalDescription() + "A item of type " + getSubType();
}

std::string Item::getStatisticalDescription() const {
    return "Weight: " + unsignedValToString(getWeight());
}

Item * Item::clone() const {
    Item * c = new Item(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}