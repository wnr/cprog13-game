#ifndef __cprog13_game__KeyHandler__
#define __cprog13_game__KeyHandler__

#include <string>

#include "Key.h"

namespace game {
    
    class KeyHandler {
    protected:
        bool locked;
        bool destroysKey;
        Key keyLock;
    public:
        KeyHandler(Key * KeyHandler);
        KeyHandler(Key * KeyHandler, bool destroysKey);
        KeyHandler(const KeyHandler & keyHandler);
        KeyHandler(KeyHandler && keyHandler);
        virtual ~KeyHandler();
        
        bool unlock(Key * key);
        
        bool isLocked() const;
        bool willDestroyKey() const;
    
        virtual std::string toString() const;
    };
}

#endif
