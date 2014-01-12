#include "Object.h"

#include "Log.h"

using namespace game;

Object::Object(std::string type, bool visible) : type(type), visible(visible) {
    log(this, "ctor");
}

Object::Object(const Object & object) : type(object.type), visible(object.visible) {
    log(this, "ctor copy");
}

Object::Object(Object && object) : type(object.type), visible(object.visible) {
    log(this, "ctor move");
}

Object::~Object() {
    log(this, "dtor");
    visible = false;
    type.clear();
}

std::string Object::getType() const {
    return type;
}

bool Object::isVisible() {
    return visible;
}

bool Object::destroy() {
    log(this, "destroyed");
    visible = false;
    return true;
}

void Object::setEnvironment(Environment * env) {
    this->env = env;
}


std::string Object::toString() const {
    return "Object(" + type + ")";
}