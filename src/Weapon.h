#ifndef __cprog13_game__Weapon__
#define __cprog13_game__Weapon__

#include <string>
#include <vector>

#include "BreakableItem.h"

namespace game {
    
    class Engine;
    
    class Weapon : public BreakableItem {
        int minDmg;
        int maxDmg;
        float critModifier;
    public:
        Weapon(unsigned int dmg, unsigned int volume);
        Weapon(std::string type, unsigned int dmg, unsigned int volume);
        Weapon(std::string type, unsigned int minDmg, unsigned int maxDmg, float critModifier, unsigned int volume);
        Weapon(std::string type, bool visible, unsigned int minDmg, unsigned int maxDmg, float critModifier, unsigned int volume);
        Weapon(const Weapon & weapon);
        Weapon(Weapon && weapon);
        virtual ~Weapon();
    };
}

#endif
