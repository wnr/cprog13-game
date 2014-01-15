#ifndef __cprog13_game__LockableContainer__
#define __cprog13_game__LockableContainer__

#include <string>

#include "Container.h"
#include "KeyHandler.h"
#include "Key.h"

namespace game {
    
    class Container;
    
    class LockableContainer : private Container, public KeyHandler {
        
    public:
        LockableContainer(std::string type, int maxSize);
        LockableContainer(std::string type, int maxSize, Key * keyLock);
        ~LockableContainer();
        
        using Container::toString;
        using Container::getMaxSize;
        using Container::getRemainingSpace;
        using Container::getDescription;
        using Container::getType;
        using Container::isVisible;
        
        virtual bool addItem(std::unique_ptr<Item> & item);
        virtual std::unique_ptr<Item> removeItem(const Item * item);
        virtual bool for_each(std::function<bool (Item * item)> & operation);
        virtual bool for_each(std::function<bool (const Item * item)> & operation) const;
        
        std::string toString() const;
    };
}

#endif
