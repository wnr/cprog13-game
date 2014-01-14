#ifndef __cprog13_game__Chest__
#define __cprog13_game__Chest__

#include <string>

#include "LockableContainer.h"
#include "Key.h"

namespace game {
    
    class Chest : public LockableContainer {
    protected:
        
    public:
        Chest(int maxSize);
        Chest(int maxSize, Key * keyLock);
        ~Chest();
        
        std::string toString() const;
    };
}

#endif
