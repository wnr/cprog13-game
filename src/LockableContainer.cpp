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

bool LockableContainer::for_each(std::function<bool (Item * item)> & operation) const {
    if(isLocked()) {
        return false;
    }
    
    Container::for_each(operation);
    
    return true;
}

std::string LockableContainer::storageListToString() const {
    if(isLocked()) {
        return "LOCKED";
    } else {
        return Container::storageListToString();
    }
}

int LockableContainer::getRemainingSpace() const {
    if(isLocked()) {
        return -1;
    }else {
        return Container::getRemainingSpace();
    }
}

int LockableContainer::getTakenSpace() const {
    if(isLocked()) {
        return -1;
    }else {
        return Container::getTakenSpace();
    }
}

Item * LockableContainer::find(const std::string & mainType, const std::string & searchString) const {
    if(isLocked()) {
        return NULL;
    } else {
        return Container::find(mainType, searchString);
    }
}

std::unique_ptr<Item> LockableContainer::push_back(std::unique_ptr<Item> element) {
    if(isLocked()) {
        return element;
    } else {
        return Container::push_back(std::move(element));
    }
}

std::unique_ptr<Item> LockableContainer::remove(const Item * element) {
    if(isLocked()) {
        return nullptr;
    } else {
        return Container::remove(element);
    }
}
