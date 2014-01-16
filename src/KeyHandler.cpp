#include "KeyHandler.h"

#include "Log.h"

using namespace game;

KeyHandler::KeyHandler(Key * keyLock) : KeyHandler(keyLock, true) {}

KeyHandler::KeyHandler(Key * keyLock, bool destroysKey) : keyLock(keyLock), destroysKey(destroysKey) {
    if(keyLock == nullptr){
        locked = false;
    } else {
        locked = true;
    }
}

KeyHandler::KeyHandler(const KeyHandler & kh) : locked(kh.locked), keyLock(kh.keyLock), destroysKey(kh.destroysKey) {}

KeyHandler::KeyHandler(KeyHandler && kh) : locked(kh.locked), keyLock(kh.keyLock), destroysKey(kh.destroysKey) {}

KeyHandler::~KeyHandler() {}

bool KeyHandler::unlock(Key * key, Container & container) {
    if(!isLocked()){
        return true;
    } else {
        if(*keyLock == *key) {
            // It is the correct type
            if(*key >= *keyLock){
                // The key is strong enough
                if(willDestroyKey()){
                    if(container.removeItem(key) == nullptr){
                        error(key, "Key should be removed from game but was not found in container.");
                    }
                }
                locked = false;
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
