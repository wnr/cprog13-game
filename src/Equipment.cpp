#include "Equipment.h"

using namespace game;

Equipment::Equipment() {}

Equipment::~Equipment() {}

std::unique_ptr<BreakableItem> Equipment::push_back(std::unique_ptr<BreakableItem> element) {
    if(findItemWithSubType(element->getSubType()) != NULL) {
        return element;
    } else {
        return GameStorage::push_back(std::move(element));
    }
}

BreakableItem * Equipment::findItemWithSubType(const std::string subType) const {
    BreakableItem * bi = find("", subType, "");
    return bi;
}