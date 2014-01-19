#include "BaseObject.h"

#include "Engine.h"

using namespace game;

BaseObject::BaseObject(std::string mainType, std::string subType) : mainType(mainType), subType(subType), tickSync(false) {}

BaseObject::BaseObject(const BaseObject & baseObject) : mainType(baseObject.mainType), subType(baseObject.subType), tickSync(baseObject.tickSync) {}

BaseObject::BaseObject(BaseObject && baseObject) : mainType(baseObject.mainType), subType(baseObject.subType), tickSync(baseObject.tickSync) {}

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

Engine & BaseObject::getEngine() const {
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