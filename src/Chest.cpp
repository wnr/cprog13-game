#include "Chest.h"
#include "Constants.h"

using namespace game;

Chest::Chest(int maxSize) : Chest(maxSize, nullptr) {}

Chest::Chest(int maxSize, Key * keyLock) : LockableContainer(CONTAINER_TYPE_CHEST, maxSize, keyLock) {}

Chest::~Chest() {}

std::string Chest::getDescription() const {
    return getSubType();
}