#include "LockableContainer.h"

using namespace game;

LockableContainer::LockableContainer(std::string subType, int maxSize) : LockableContainer(subType, maxSize, nullptr) {}

LockableContainer::LockableContainer(std::string subType, int maxSize, Key * matchingKey) : LockableContainer(subType, maxSize, matchingKey, subType) {}

LockableContainer::LockableContainer(std::string subType, int maxSize, Key * matchingKey, std::string name) : Container(subType, maxSize, name), KeyLock(matchingKey) {}

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

std::string LockableContainer::getDescription() const {
    std::string desc = getPersonalDescription() + "\n" + getStatisticalDescription();
    if(!isLocked()){
        desc += "\n";
        desc += TEXT_DIVIDER;
        desc += "\n" + getStorageListAsString();
    }
    return desc;
}

std::string LockableContainer::getStorageListAsString(const std::vector<const Item*> skips, const std::string & itemPrefix) const {
    if(isLocked()) {
        return INFORMATION_UNKNOWN;
    } else {
        return Container::getStorageListAsString(skips, itemPrefix);
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

Item * LockableContainer::find(const std::string & mainType, std::string searchString, bool caseinsens) const {
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

std::string LockableContainer::getStatisticalDescription() const {
    return Container::getStatisticalDescription() + "\n" + KeyLock::getStatisticalDescription();
}
