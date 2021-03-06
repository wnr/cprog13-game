#include "BaseObject.h"

#include "Engine.h"

using namespace game;

BaseObject::BaseObject(std::string mainType, std::string subType) : BaseObject(mainType, subType, subType) {}

BaseObject::BaseObject(std::string mainType, std::string subType, std::string name) : mainType(mainType), subType(subType), name(name), tickSync(false) {}

BaseObject::BaseObject(const BaseObject & obj)   : mainType(obj.mainType), subType(obj.subType), tickSync(obj.tickSync), name(obj.name) {}
BaseObject::BaseObject(BaseObject && obj)        : mainType(obj.mainType), subType(obj.subType), tickSync(obj.tickSync), name(obj.name) {}

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

Engine * BaseObject::getEngine() const {
    return Engine::getInstance();
}

bool BaseObject::getTickSync() const {
    return tickSync;
}

void BaseObject::setTickSync(bool ts) {
    tickSync = ts;
}

void BaseObject::tick() {
    setTickSync(!getTickSync());
}

void BaseObject::update() {
    tick();
}

std::string BaseObject::getName() const {
    return name;
}