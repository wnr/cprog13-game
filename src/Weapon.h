#ifndef __cprog13_game__Weapon__
#define __cprog13_game__Weapon__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include <string>
#include <vector>

#include "Item.h"

namespace game {
    
    class Engine;
    
    class Weapon : public Item {
    protected:
        int minDmg;
        int maxDmg;
        float critModifier;
    public:
        Weapon(Engine * engine, int dmg);
        Weapon(Engine * engine, std::string type, int minDmg, int maxDmg, float critModifier);
        Weapon(Engine * engine, std::string type, bool visible, bool breakable, bool working, int minDmg, int maxDmg, float critModifier);
        Weapon(const Weapon & weapon);
        Weapon(Weapon && weapon);
        virtual ~Weapon();
    
        virtual std::string toString() const;
    };
}

#endif
