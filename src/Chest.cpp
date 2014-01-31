#include "Chest.h"
#include "Constants.h"

using namespace game;

Chest::Chest() : Chest(CHEST_SIZE) {}

Chest::Chest(std::string name) : Chest(CHEST_SIZE, nullptr, name) {}

Chest::Chest(int maxSize) : Chest(maxSize, nullptr) {}

Chest::Chest(int maxSize, Key * keyLock) : Chest(maxSize, keyLock, CONTAINER_TYPE_CHEST) {}

Chest::Chest(int maxSize, Key * keyLock, std::string name) : LockableContainer(CONTAINER_TYPE_CHEST, maxSize, keyLock, name) {}

Chest::Chest(const Chest & chest)   : LockableContainer(chest) {}
Chest::Chest(Chest && chest)        : LockableContainer(chest) {}

Chest::~Chest() {}


Chest * Chest::clone() const {
    Chest * c = new Chest(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}