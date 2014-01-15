#include "Object.h"

#include "Log.h"
#include "Engine.h"

using namespace game;

Object::Object(std::string type) : Object(type, true) {}

Object::Object(std::string type, bool visible) : type(type), visible(visible) {}

Object::Object(const Object & object) : type(object.type), visible(object.visible) {}

Object::Object(Object && object) : type(object.type), visible(object.visible) {}

Object::~Object() {}

std::string Object::getType() const {
    return type;
}

bool Object::isVisible() const {
    return visible;
}

Engine & Object::getEngine() const {
    return Engine::getInstance();
}

std::string Object::toString() const {
    return "Object(" + type + ")";
}