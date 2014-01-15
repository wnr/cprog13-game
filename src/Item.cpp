#include "Item.h"

#include "Log.h"

using namespace game;

Item::Item(std::string type) : Item(type, true) {}

Item::Item(std::string type, bool visible) : Object(type, visible) {}

Item::Item(const Item & item) : Object(item) {}

Item::Item(Item && item) : Object(item) {}

Item::~Item() {}

unsigned int Item::getVolume() const {
    return volume;
}

std::string Item::toString() const {
    return "Item(" + getType() + ")";
}

std::string Item::getDescription() const {
    return getType();
}

int operator+=(int value, const Item & item) {
    return value + item.getVolume();
}

int operator+(const Item & item1, const Item & item2) {
    return item1.getVolume() + item2.getVolume();
}

bool operator<(int value, const game::Item & item) {
    return value < item.getVolume();
};