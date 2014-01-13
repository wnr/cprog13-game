#include "Item.h"

#include "Log.h"

using namespace game;

Item::Item(Engine * engine, std::string type) : Item(engine, type, true, true) {}

Item::Item(Engine * engine, std::string type, bool visible, bool breakable) : Item(engine, type, visible, breakable, true) {}

Item::Item(Engine * engine, std::string type, bool visible, bool breakable, bool working) : Object(engine, type, visible, true), breakable(breakable), working(working) {
    if(!breakable && !working){
        error(this, "Item can't be both unbreakable and broken.");
    }
}

Item::Item(const Item & item) : Object(item), breakable(item.breakable), working(item.working) {}

Item::Item(Item && item) : Object(item), breakable(item.breakable), working(item.working) {} //TODO: Might be bad to use ctor.

Item::~Item() {}

std::string Item::getType() const {
    return type;
}

bool Item::isVisible() const {
    return visible;
}

bool Item::isBreakable() const {
    return breakable;
}

bool Item::isWorking() const {
    return working;
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
    return "Item(" + type + ")";
}

std::string Item::getDescription() const {
    return type;
}