#include "PhysicalObject.h"

#include "Log.h"

using namespace game;

PhysicalObject::PhysicalObject(std::string mainType, std::string subType) : PhysicalObject(mainType, subType, true) {}

PhysicalObject::PhysicalObject(std::string mainType, std::string subType, bool visible) : BaseObject(mainType, subType), visible(visible) {}

PhysicalObject::PhysicalObject(const PhysicalObject & pObject) : BaseObject(pObject), visible(pObject.visible) {}

PhysicalObject::PhysicalObject(PhysicalObject && pObject) : BaseObject(pObject), visible(pObject.visible) {}

PhysicalObject::~PhysicalObject() {}

bool PhysicalObject::isVisible() const {
    return visible;
}

bool PhysicalObject::isContainer() const {
    return getMainType() == OBJECT_CONTAINER_TYPE;
}

bool PhysicalObject::isEntity() const {
    return getMainType() == OBJECT_ENTITY_TYPE;
}

bool PhysicalObject::isItem() const {
    return getMainType() == OBJECT_ITEM_TYPE;
}

void PhysicalObject::update() {}