#include "Backpack.h"
#include "Constants.h"

using namespace game;

Backpack::Backpack(int maxSize) : Container(CONTAINER_BACKPACK_TYPE, maxSize){}

Backpack::~Backpack() {}

std::string Backpack::getDescription() const {
    return getSubType();
}