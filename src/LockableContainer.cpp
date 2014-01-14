#include "LockableContainer.h"

using namespace game;

LockableContainer::LockableContainer(std::string type, int maxSize) : LockableContainer(type, maxSize, nullptr) {}

LockableContainer::LockableContainer(std::string type, int maxSize, Key * keyLock) : Container(type, maxSize, true, false), KeyHandler(keyLock) {}

LockableContainer::~LockableContainer() {}

bool LockableContainer::addItem(std::unique_ptr<Item> & item) {
    if(!locked){
        return Container::addItem(item);
    } else {
        return false;
    }
}

std::unique_ptr<Item> LockableContainer::removeItem(const Item * item) {
    if(!locked){
        return Container::removeItem(item);
    } else {
        return nullptr;
    }
}

const std::vector<std::unique_ptr<Item>> * LockableContainer::getInventory() const {
    if(!locked) {
        return Container::getInventory();
    } else {
        return nullptr;
    }
}

std::string LockableContainer::toString() const {
    return type;
}