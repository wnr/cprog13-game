#include "Chest.h"
#include "Constants.h"

using namespace game;

Chest::Chest(int maxSize) : Chest(maxSize, nullptr) {}

Chest::Chest(int maxSize, Key * keyLock) : Chest(maxSize, keyLock, CONTAINER_TYPE_CHEST) {}

Chest::Chest(int maxSize, Key * keyLock, std::string name) : LockableContainer(CONTAINER_TYPE_CHEST, maxSize, keyLock, name) {}

Chest::~Chest() {}