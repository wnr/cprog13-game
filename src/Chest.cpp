#include "Chest.h"
#include "Constants.h"

using namespace game;

Chest::Chest(int maxSize) : Chest(maxSize, nullptr) {}

Chest::Chest(int maxSize, Key * keyLock) : LockableContainer(CONTAINER_CHEST_TYPE, maxSize, keyLock) {}

Chest::~Chest() {}

std::string Chest::getDescription() const {
    return getSubType();
}