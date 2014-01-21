#ifndef __cprog13_game__KeyLock__
#define __cprog13_game__KeyLock__

#include <string>

#include "Key.h"
#include "Container.h"

namespace game {
    
    class Container;
    
    class KeyLock {
        bool locked;
        bool destroysKey;
        Key * matchingKey;
    public:
        KeyLock(Key * matchingKey);
        KeyLock(Key * matchingKey, bool destroysKey);
        KeyLock(const KeyLock & keyLock);
        KeyLock(KeyLock && keyLock);
        virtual ~KeyLock();
        
        bool unlock(Key * matchingKey, Container & container);
        
        bool isLocked() const;
        bool willDestroyKey() const;
    
    protected:
        std::string getStatisticalDescription() const;
        std::string getLockedString() const;
    };
}

#endif
