#include "Inventory.h"
#include "Constants.h"

using namespace game;

Inventory::Inventory(int maxSize) : Container(CONTAINER_TYPE_INVENTORY, maxSize){}

Inventory::Inventory(const Inventory & inv)     : Container(inv) {}
Inventory::Inventory(Inventory && inv)          : Container(inv) {}

Inventory::~Inventory() {}