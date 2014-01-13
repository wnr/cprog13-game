#include "Object.h"

#include "Log.h"

using namespace game;

Object::Object(Engine * engine, std::string type) : Object(engine, type, true, true){}

Object::Object(Engine * engine, std::string type, bool visible, bool carriable) : engine(engine), visible(visible), carriable(carriable) {
    log(this, "ctor");
}

Object::Object(const Object & object) : Object(object.engine, object.type, object.visible, object.carriable) {
    log(this, "ctor copy");
}

Object::Object(Object && object) : Object(object.engine, object.type, object.visible, object.carriable) { //TODO test if this works.
    log(this, "ctor move");
}

Object::~Object() {
    log(this, "dtor");
    visible = false;
    carriable = false;
    type.clear();
}

std::string Object::getType() const {
    return type;
}

bool Object::isVisible() const {
    return visible;
}

bool Object::isCarriable() const {
    return carriable;
}

std::string Object::toString() const {
    return "Object(" + type + ")";
}