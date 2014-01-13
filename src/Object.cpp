#include "Object.h"

#include "Log.h"
#include "Engine.h"

using namespace game;

Object::Object(std::string type) : Object(type, true, true) {}

Object::Object(std::string type, bool visible, bool carriable) : type(type), visible(visible), carriable(carriable) {}

Object::Object(const Object & object) : type(object.type), visible(object.visible), carriable(object.carriable) {}

Object::Object(Object && object) : type(object.type), visible(object.visible), carriable(object.carriable) {}

Object::~Object() {}

std::string Object::getType() const {
    return type;
}

bool Object::isVisible() const {
    return visible;
}

bool Object::isCarriable() const {
    return carriable;
}

Engine & Object::getEngine() const {
    return Engine::getInstance();
}

std::string Object::toString() const {
    return "Object(" + type + ")";
}