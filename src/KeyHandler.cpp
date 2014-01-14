#include "KeyHandler.h"

using namespace game;

KeyHandler::KeyHandler(Key * keyLock) : KeyHandler(keyLock, true) {}

KeyHandler::KeyHandler(Key * keyLock, bool destroysKey) : keyLock(*keyLock), destroysKey(destroysKey) {
    if(keyLock == nullptr){
        locked = false;
    } else {
        locked = true;
    }
}

KeyHandler::KeyHandler(const KeyHandler & kh) : locked(kh.locked), keyLock(kh.keyLock), destroysKey(kh.destroysKey) {}

KeyHandler::KeyHandler(KeyHandler && kh) : locked(kh.locked), keyLock(kh.keyLock), destroysKey(kh.destroysKey) {}

KeyHandler::~KeyHandler() {}

bool KeyHandler::unlock(Key * key) {
    if(!isLocked()){
        return true;
    } else {
        if(keyLock == *key) {
            // It is the correct type
            if(*key >= keyLock){
                // The key is strong enough
                locked = false;
                if(willDestroyKey()){
                    delete key;
                }
                return true;
            }
        }
    }
    return false;
}

bool KeyHandler::isLocked() const {
    return locked;
}

bool KeyHandler::willDestroyKey() const {
    return destroysKey;
}

std::string KeyHandler::toString() const {
    return keyLock.toString();
}
