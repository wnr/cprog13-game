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

void Object::setEnvironment(Environment * env) {
    this->env = env;
}

Environment * Object::getEnvironment() const {
    return env;
}

bool Object::move(const std::string &direction) {
    if(env == NULL) {
        error(this, "Entity does not have an Environment.");
        return false;
    }
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    log(this, "move " + direction);
    
    neighbor->addObject(env->removeObject(this));
    
    return true;
}

std::string Object::toString() const {
    return "Object(" + type + ")";
}

void Object::update(const Environment & env) {}