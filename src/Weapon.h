#ifndef __cprog13_game__Weapon__
#define __cprog13_game__Weapon__

#include <string>
#include <vector>

#include "Item.h"

namespace game {
    
    class Engine;
    
    class Weapon : public Item {
        int minDmg;
        int maxDmg;
        float critModifier;
    public:
        Weapon(int dmg);
        Weapon(std::string type, int minDmg, int maxDmg, float critModifier);
        Weapon(std::string type, bool visible, bool breakable, bool working, int minDmg, int maxDmg, float critModifier);
        Weapon(const Weapon & weapon);
        Weapon(Weapon && weapon);
        virtual ~Weapon();
    
        virtual std::string toString() const;
    };
}

#endif
