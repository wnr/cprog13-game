#include "Container.h"
#include "Item.h"
#include "Constants.h"

using namespace game;

Container::Container(std::string subType, unsigned int maxSize) : Container(subType, maxSize, subType) {}

Container::Container(std::string subType, unsigned int maxSize, std::string name) : PhysicalObject(OBJECT_TYPE_CONTAINER, subType, name), maxSize(maxSize) {}

Container::Container(const Container & container) : PhysicalObject(container), maxSize(container.maxSize) {}

Container::Container(Container && container) : PhysicalObject(container), maxSize(container.maxSize) {}

Container::~Container() {}

std::unique_ptr<Item> Container::push_back(std::unique_ptr<Item> item) {
    if(getRemainingSpace() < *item) {
        return item;
    }
    
    return GameStorage<Item>::push_back(std::move(item));
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
    PhysicalObject::update();
    
    for_each([](Item * item) -> bool {
        item->update();
        return true;
    });
}

std::string Container::getDescription() const {
    return getPersonalDescription() + "\n" + getStatisticalDescription() + "\n" + TEXT_DIVIDER + "\n" + getStorageListAsString();
}

std::string Container::getPersonalDescription() const {
    return PhysicalObject::getPersonalDescription() + "Items can be stored here.";
}

std::string Container::getStatisticalDescription() const {
    return "Taken space/Max space: (" + unsignedValToString(getTakenSpace()) + "/" + unsignedValToString(getMaxSize()) + ")";
}
