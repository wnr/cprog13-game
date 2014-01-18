#include "PhysicalObject.h"
#include "Environment.h"
#include "Constants.h"
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
    return getMainType() == OBJECT_TYPE_CONTAINER;
}

bool PhysicalObject::isEntity() const {
    return getMainType() == OBJECT_TYPE_ENTITY;
}

bool PhysicalObject::isItem() const {
    return getMainType() == OBJECT_TYPE_ITEM;
}

void PhysicalObject::update() {}