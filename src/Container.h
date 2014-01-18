#ifndef __cprog13_game__Container__
#define __cprog13_game__Container__

#include <string>
#include <vector>

#include "PhysicalObject.h"
#include "OwningStorage.h"
#include "Item.h"

namespace game {
    
    class Engine;
    
    class Container : public PhysicalObject, public OwningStorage<Item> {
        const unsigned int maxSize;
    public:
        Container(std::string type, unsigned int maxSize);
        Container(std::string type, unsigned int maxSize, bool visible);
        Container(const Container & container);
        Container(Container && container);
        ~Container();

        unsigned int getMaxSize() const;
        unsigned int getRemainingSpace() const;
        virtual bool addItem(std::unique_ptr<Item> & item);
        virtual std::unique_ptr<Item> removeItem(const Item * item);
    };
}

#endif
