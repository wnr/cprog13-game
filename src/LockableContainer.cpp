#include "LockableContainer.h"

using namespace game;

LockableContainer::LockableContainer(std::string type, int maxSize) : LockableContainer(type, maxSize, nullptr) {}

LockableContainer::LockableContainer(std::string type, int maxSize, Key * keyLock) : Container(type, maxSize, true), KeyHandler(keyLock) {}

LockableContainer::~LockableContainer() {}

bool LockableContainer::addItem(std::unique_ptr<Item> & item) {
    if(isLocked()) {
        return false;
    }
    
    return Container::addItem(item);
}

std::unique_ptr<Item> LockableContainer::removeItem(const Item * item) {
    if(isLocked()) {
        return nullptr;
    }
    
    return Container::removeItem(item);
}

bool LockableContainer::for_each(std::function<bool (Item * item)> & operation) {
    if(isLocked()) {
        return false;
    }
    
    Container::for_each(operation);
    
    return true;
}

bool LockableContainer::for_each(std::function<bool (const Item * item)> & operation) const {
    if(isLocked()) {
        return false;
    }
    
    Container::for_each(operation);
    
    return true;
}

std::string LockableContainer::toString() const {
    return getType();
}