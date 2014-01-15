#include "Object.h"

#include "Log.h"
#include "Engine.h"

using namespace game;

Object::Object(std::string mainType, std::string subType) : Object(mainType, subType, true) {}

Object::Object(std::string mainType, std::string subType, bool visible) : mainType(mainType), subType(subType), visible(visible) {}

Object::Object(const Object & object) : mainType(object.mainType), subType(object.subType), visible(object.visible) {}

Object::Object(Object && object) : mainType(object.mainType), subType(object.subType), visible(object.visible) {}

Object::~Object() {}

std::string Object::getMainType() const {
    return mainType;
}

std::string Object::getSubType() const {
    return subType;
}

bool Object::isVisible() const {
    return visible;
}

bool Object::isContainer() const {
    return getMainType() == OBJECT_CONTAINER_TYPE;
}

bool Object::isEntity() const {
    return getMainType() == OBJECT_ENTITY_TYPE;
}

bool Object::isItem() const {
    return getMainType() == OBJECT_ITEM_TYPE;
}

Engine & Object::getEngine() const {
    return Engine::getInstance();
}

std::string Object::toString() const {
    return getMainType() + "(" + getSubType() + ")";
}

void Object::update(Environment & env) {}