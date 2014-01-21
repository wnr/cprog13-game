#ifndef __cprog13_game__LockableContainer__
#define __cprog13_game__LockableContainer__

#include <string>

#include "Container.h"
#include "KeyLock.h"
#include "Key.h"

namespace game {
    
    class Container;
    
    class LockableContainer : public Container, public KeyLock {
        
    public:
        LockableContainer(std::string subType, int maxSize);
        LockableContainer(std::string subType, int maxSize, Key * matchingKey);
        LockableContainer(std::string subType, int maxSize, Key * matchingKey, std::string name);
        ~LockableContainer();
        
        bool addItem(std::unique_ptr<Item> & item);
        std::unique_ptr<Item> removeItem(const Item * item);
        bool for_each(std::function<bool (Item * item)> & operation) const;
        
        Item * find(const std::string & mainType, const std::string & subType, std::string searchString, bool caseinsens = true) const;
        std::unique_ptr<Item> push_back(std::unique_ptr<Item> element);
        std::unique_ptr<Item> remove(const Item * element);
        virtual std::string getStorageListAsString(const std::vector<const Item*> skips = {}, const std::string & itemPrefix = LIST_ITEM_PREFIX) const;
        int getRemainingSpace() const;
        int getTakenSpace() const;
        
        virtual std::string getDescription() const;
        
    protected:
        virtual std::string getStatisticalDescription() const;
    };
}

#endif
