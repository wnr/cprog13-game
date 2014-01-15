#ifndef __cprog13_game__Backpack__
#define __cprog13_game__Backpack__

#include <string>

#include "Container.h"

namespace game {
    
    class Backpack : public Container {
    public:
        Backpack(int maxSize);
        ~Backpack();
    
        std::string toString() const;
    };
}

#endif
