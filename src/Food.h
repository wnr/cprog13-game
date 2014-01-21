#ifndef __cprog13_game__Food__
#define __cprog13_game__Food__

#include <string>
#include <vector>
#include "Item.h"

namespace game {
    class Food : public Item {
        unsigned int strength;
        
        public:
        Food();
        Food(std::string name);
        Food(std::string name, unsigned int strength);
        Food(std::string name, unsigned int strength, unsigned int weight);
        Food(const Food & food);
        Food(Food && food);
        virtual ~Food();
        
        unsigned int getStrength() const;
    };
}

#endif