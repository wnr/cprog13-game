#include "Item.h"

#include "Log.h"

using namespace game;

Item::Item(std::string type) : Item(type, true, true) {}

Item::Item(std::string type, bool visible, bool breakable) : Item(type, visible, breakable, true) {}

Item::Item(std::string type, bool visible, bool breakable, bool working) : Object(type, visible, true), breakable(breakable), working(working) {
    if(!breakable && !working){
        throw std::logic_error("Items can't be both unbreakable and broken.");
    }
}

Item::Item(const Item & item) : Object(item), breakable(item.breakable), working(item.working) {}

Item::Item(Item && item) : Object(item), breakable(item.breakable), working(item.working) {}

Item::~Item() {}

bool Item::isBreakable() const {
    return breakable;
}

bool Item::isWorking() const {
    return working;
}

unsigned int Item::getVolume() const {
    return volume;
}

bool Item::breakItem() {
    if(!breakable || !working){
        return false;
    }
    
    log(this, "broke");
    working = false;
    return true;
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