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
        float critModifier;
        
    public:
        Weapon(unsigned int dmg, unsigned int weight);
        Weapon(std::string name, unsigned int dmg, unsigned int weight);
        Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int weight);
        Weapon(std::string name, unsigned int minDmg, unsigned int maxDmg, unsigned int critProb, float critModifier, unsigned int weight);
        Weapon(const Weapon & weapon);
        Weapon(Weapon && weapon);
        virtual ~Weapon();
        
        int getMinDmg() const;
        int getMaxDmg() const;
        int getCritProb() const;
        float getCritModifier() const;
        
    protected:
        virtual std::string getStatisticalDescription() const;
    };
}

#endif
