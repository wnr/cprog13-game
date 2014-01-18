#ifndef __cprog13_game__LockableContainer__
#define __cprog13_game__LockableContainer__

#include <string>

#include "Container.h"
#include "KeyHandler.h"
#include "Key.h"

namespace game {
    
    class Container;
    
    class LockableContainer : public Container, public KeyHandler {
        
    public:
        LockableContainer(std::string type, int maxSize);
        LockableContainer(std::string type, int maxSize, Key * keyLock);
        ~LockableContainer();
        
        bool addItem(std::unique_ptr<Item> & item);
        std::unique_ptr<Item> removeItem(const Item * item);
        bool for_each(std::function<bool (Item * item)> & operation) const;
        
        Item * find(const std::string & mainType, std::string searchString, bool caseinsens = true) const;
        std::unique_ptr<Item> push_back(std::unique_ptr<Item> element);
        std::unique_ptr<Item> remove(const Item * element);
        std::string storageListToString() const;
        int getRemainingSpace() const;
        int getTakenSpace() const;
    };
}

#endif
