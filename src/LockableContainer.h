#ifndef __cprog13_game__LockableContainer__
#define __cprog13_game__LockableContainer__

#include <string>

#include "Container.h"
#include "KeyHandler.h"
#include "Key.h"

namespace game {
    
    class Container;
    
    class LockableContainer : public Container, public KeyHandler {
    protected:
        
    public:
        LockableContainer(std::string type, int maxSize);
        LockableContainer(std::string type, int maxSize, Key * keyLock);
        ~LockableContainer();
        
        virtual bool addItem(std::unique_ptr<Item> & item);
        virtual std::unique_ptr<Item> removeItem(const Item * item);
        virtual const std::vector<std::unique_ptr<Item>> * getInventory() const;
        
        std::string toString() const;
    };
}

#endif