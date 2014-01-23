#ifndef __cprog13_game__Weapon__
#define __cprog13_game__Weapon__

#include <string>
#include <vector>

#include "BreakableItem.h"

namespace game {
    
    class Engine;
    
    class Weapon : public BreakableItem {
        unsigned int minDmg;
        unsigned int maxDmg;
        unsigned int critProb;
        unsigned int critModifier;
        
    public:
        Weapon(unsigned int dmg, unsigned int weight);
        Weapon(std::string name, unsigned int dmg, unsigned int weight);
        Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int weight);
        Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int weight, unsigned int critProb, unsigned int critMod);
        Weapon(const Weapon & weapon);
        Weapon(Weapon && weapon);
        virtual ~Weapon();
        
        virtual bool affectDurability(unsigned int power);
        
        unsigned int getMinDmg() const;
        unsigned int getMaxDmg() const;
        unsigned int getCritProb() const;
        unsigned int getCritModifier() const;
        
    protected:
        virtual std::string getStatisticalDescription() const;
    };
}

#endif
