#include "PhysicalObject.h"
#include "Environment.h"
#include "Constants.h"

using namespace game;

PhysicalObject::PhysicalObject(std::string mainType, std::string subType) : PhysicalObject(mainType, subType, subType) {}

PhysicalObject::PhysicalObject(std::string mainType, std::string subType, std::string name) : BaseObject(mainType, subType, name) {}

PhysicalObject::PhysicalObject(const PhysicalObject & pObject) : BaseObject(pObject) {}

PhysicalObject::PhysicalObject(PhysicalObject && pObject) : BaseObject(pObject) {}

PhysicalObject::~PhysicalObject() {}


bool PhysicalObject::isContainer() const {
    return getMainType() == OBJECT_TYPE_CONTAINER;
}

bool PhysicalObject::isCharacter() const {
    return getMainType() == OBJECT_TYPE_CHARACTER;
}

bool PhysicalObject::isItem() const {
    return getMainType() == OBJECT_TYPE_ITEM;
}