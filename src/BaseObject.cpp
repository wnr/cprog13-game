#include "BaseObject.h"

#include "Log.h"
#include "Engine.h"

using namespace game;

BaseObject::BaseObject(std::string mainType, std::string subType) : mainType(mainType), subType(subType) {}

BaseObject::BaseObject(const BaseObject & baseObject) : mainType(baseObject.mainType), subType(baseObject.subType) {}

BaseObject::BaseObject(BaseObject && baseObject) : mainType(baseObject.mainType), subType(baseObject.subType) {}

BaseObject::~BaseObject() {}

std::string BaseObject::getMainType() const {
    return mainType;
}

std::string BaseObject::getSubType() const {
    return subType;
}

std::string BaseObject::toString() const {
    return getMainType() + "(" + getSubType() + ")";
}

Engine & BaseObject::getEngine() const{
    return Engine::getInstance();
}