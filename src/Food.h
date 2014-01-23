#ifndef __cprog13_game__Food__
#define __cprog13_game__Food__

#include <string>
#include "Consumable.h"

namespace game {
    class Food : public Consumable {
        
    public:
        Food(std::string name);
        Food(std::string name, unsigned int strength);
        Food(std::string name, unsigned int strength, unsigned int weight);
        Food(const Food & food);
        Food(Food && food);
        virtual ~Food();
        
        virtual std::string consume(Character *) const;
        void addHealth(int amount, Character * character) const;
    };
    
}

#endif