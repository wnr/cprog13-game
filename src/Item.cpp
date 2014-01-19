#include "Item.h"

using namespace game;

Item::Item(std::string type, unsigned int volume) : Item(type, true, volume) {}

Item::Item(std::string type, bool visible, unsigned int volume) : PhysicalObject(OBJECT_TYPE_ITEM, type, visible), volume(volume){}

Item::Item(const Item & item) : PhysicalObject(item), volume(item.volume) {}

Item::Item(Item && item) : PhysicalObject(item), volume(item.volume) {}

Item::~Item() {}

unsigned int Item::getVolume() const {
    return volume;
}

std::string Item::getDescription() const {
    return getSubType();
}

void Item::update() {
    PhysicalObject::update();
}

int operator+=(int & value, const Item & item) {
    return value += item.getVolume();
}

int operator+(const Item & item1, const Item & item2) {
    return item1.getVolume() + item2.getVolume();
}

bool operator<(int value, const game::Item & item) {
    return value < item.getVolume();
};