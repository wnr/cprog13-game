#ifndef __cprog13_game__Inventory__
#define __cprog13_game__Inventory__

#include <string>

#include "Container.h"

namespace game {
    
    class Inventory : public Container {
    public:
        Inventory(int maxSize);
        Inventory(const Inventory & inv);
        Inventory(Inventory && inv);
        
        virtual ~Inventory();
    };
}

#endif
