#include "Container.h"

using namespace game;

Container::Container(std::string type, int maxSize) : Container(type, maxSize, true, true){}

Container::Container(std::string type, int maxSize, bool visible, bool carriable) : Object(type, visible, carriable), maxSize(maxSize) {}

Container::Container(const Container & con) : Object(con), maxSize(con.maxSize) {}

Container::Container(Container && con) : Object(con), maxSize(con.maxSize) {}

Container::~Container() {}

bool Container::addItem(std::unique_ptr<Item> & item) {
    if(getRemainingSpace() >= item->getVolume()){
        inventory->push_back(std::move(item));
        return true;
    }else{
        return false;
    }
}

std::unique_ptr<Item> Container::removeItem(const Item * item) {
    for (std::vector<std::unique_ptr<Item>>::iterator it = (*inventory).begin(); it != (*inventory).end(); it++){
        if((*it).get() == item){
            std::unique_ptr<Item> returnP = std::move(*it);
            (*inventory).erase(it);
            return returnP;
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Item>> * Container::getInventory() const {
    return inventory;
}

int Container::getRemainingSpace() const {
    int takenSpace = 0;
    for (const auto & item : *getInventory()){
        takenSpace += *item;
    }
    return getMaxSize() - takenSpace;
}

int Container::getMaxSize() const {
    return maxSize;
}

std::string Container::toString() const {
    return "Container(" + type + ")";
}

std::string Container::getDescription() const {
    return type;
}