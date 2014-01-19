#include "Container.h"
#include "Item.h"

using namespace game;

Container::Container(std::string type, unsigned int maxSize) : Container(type, maxSize, true) {}

Container::Container(std::string type, unsigned int maxSize, bool visible) : PhysicalObject(OBJECT_TYPE_CONTAINER, type, visible), maxSize(maxSize) {}

Container::Container(const Container & container) : PhysicalObject(container), maxSize(container.maxSize) {}

Container::Container(Container && container) : PhysicalObject(container), maxSize(container.maxSize) {}

Container::~Container() {}

bool Container::addItem(std::unique_ptr<Item> & item) {
    if(getRemainingSpace() < *item) {
        return false;
    }
    
    push_back(std::move(item));
    
    return true;
}

std::unique_ptr<Item> Container::removeItem(const Item * item) {
    return remove(item);
}

int Container::getRemainingSpace() const {
    
    return getMaxSize() - getTakenSpace();
}

int Container::getTakenSpace() const {
    int takenSpace = 0;
    
    for_each([&takenSpace] (const Item * item) {
        takenSpace += *item;
        return true;
    });
    
    return takenSpace;
}

unsigned int Container::getMaxSize() const {
    return maxSize;
}

void Container::update() {
    for_each([](Item * item) -> bool {
        item->update();
        return true;
    });
}