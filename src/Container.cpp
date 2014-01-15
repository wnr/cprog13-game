#include "Container.h"
#include "Item.h"

using namespace game;

Container::Container(std::string type, unsigned int maxSize) : Container(type, maxSize, true, true){}

Container::Container(std::string type, unsigned int maxSize, bool visible, bool carriable) : Object(type, visible, carriable), maxSize(maxSize) {}

Container::Container(const Container & container) : Object(container), maxSize(container.maxSize) {}

Container::Container(Container && container) : Object(container), maxSize(container.maxSize) {}

Container::~Container() {}

bool Container::addItem(std::unique_ptr<Item> & item) {
    if(getRemainingSpace() >= item->getVolume()) { //Use operator?
        inventory.push_back(std::move(item));
        return true;
    } else {
        return false;
    }
}

std::unique_ptr<Item> Container::removeItem(const Item * item) {
    std::unique_ptr<Item> removed;
    
    auto it = std::remove_if(inventory.begin(), inventory.end(), [item, &removed] (std::unique_ptr<Item> & ptr) -> bool {
        //TODO: Can equality be checked like this? If the pointers are pointing to the same address they should be the same...
        if(ptr.get() == item) {
            removed = std::move(ptr);
            return true;
        }
        
        return false;
    });
    
    inventory.erase(it, inventory.end()); //TODO: Won't this erase everything from it to end?
    
    return removed;
}

const std::vector<std::unique_ptr<Item>> * Container::getInventory() const {
    return &inventory;
}

unsigned int Container::getRemainingSpace() const {
    unsigned int takenSpace = 0;
    for (const auto & item : inventory){
        takenSpace += *item;
    }
    return getMaxSize() - takenSpace;
}

unsigned int Container::getMaxSize() const {
    return maxSize;
}

std::string Container::toString() const {
    return "Container(" + type + ")";
}

std::string Container::getDescription() const {
    return type;
}