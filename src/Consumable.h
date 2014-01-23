#ifndef __cprog13_game__Consumable__
#define __cprog13_game__Consumable__

#include <string>
#include "Item.h"

namespace game {
    class Character;
    class Consumable : public Item {
        unsigned int potency;
        
        public:
        Consumable(std::string name, unsigned int potency, unsigned int weight);
        Consumable(const Consumable & consumable);
        Consumable(Consumable && consumable);
        virtual ~Consumable();
        
        unsigned int getPotency() const;
        
        virtual std::string consume(Character *) const = 0;
    };
}

#endif