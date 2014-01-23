#ifndef __cprog13_game__Potion__
#define __cprog13_game__Potion__

#include <string>
#include <vector>
#include "Consumable.h"

namespace game {
    class Potion : public Consumable {
        
        public:
        Potion(std::string name);
        Potion(std::string name, unsigned int potency);
        Potion(std::string name, unsigned int potency, unsigned int weight);
        Potion(const Potion & potion);
        Potion(Potion && potion);
        virtual ~Potion();
        
        virtual std::string consume(Character *) const;
        void addMaxHealth(int amount, Character * character) const;
    };
}

#endif