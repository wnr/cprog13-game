#include "KeyLock.h"
#include "utils.h"

using namespace game;

KeyLock::KeyLock(Key * matchingKey) : KeyLock(matchingKey, true) {}

KeyLock::KeyLock(Key * matchingKey, bool destroysKey) : matchingKey(matchingKey), destroysKey(destroysKey) {
    if(matchingKey == nullptr){
        locked = false;
    } else {
        locked = true;
    }
}

KeyLock::KeyLock(const KeyLock & kh) : locked(kh.locked), matchingKey(kh.matchingKey), destroysKey(kh.destroysKey) {}

KeyLock::KeyLock(KeyLock && kh) : locked(kh.locked), matchingKey(kh.matchingKey), destroysKey(kh.destroysKey) {}

KeyLock::~KeyLock() {}

bool KeyLock::unlock(Key * key, Container & container) {
    if(!isLocked()){
        return true;
    } else {
        if(*matchingKey == *key) {
            // It is the correct type
            if(*key >= *matchingKey){
                // The key is strong enough
                if(willDestroyKey()){
                    if(container.remove(key) == nullptr){
                        throw std::runtime_error("Key should be removed from game but was not found in container.");
                    }
                }
                locked = false;
                return true;
            }
        }
    }
    return false;
}

bool KeyLock::isLocked() const {
    return locked;
}

bool KeyLock::willDestroyKey() const {
    return destroysKey;
}

std::string KeyLock::getLockedString() const {
    if(isLocked()) {
        return "LOCKED";
    } else {
        return "UNLOCKED";
    }
}

std::string KeyLock::getStatisticalDescription() const {
    std::string desc = getLockedString();
    if(isLocked()) {
        desc.append("\nLock type: " + matchingKey->getIdentifier());
        desc.append("\nLock level: " + unsignedValToString(matchingKey->getLevel()));
        if(willDestroyKey()) {
            desc.append("\nKey used to unlock will get destroyed!");
        }
    }
    return desc;
}
