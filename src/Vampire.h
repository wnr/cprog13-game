#ifndef __cprog13_game__Vampire__
#define __cprog13_game__Vampire__

#include "Monster.h"

namespace game {
    class Environment;
    
    class Vampire : public Monster {
    public:
        Vampire(Environment * env);
        Vampire(Environment * env, std::string subType, unsigned int maxHealth);
        Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb);
        Vampire(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod);
        Vampire(const Vampire & vampire);
        Vampire(Vampire && vampire);
        virtual ~Vampire();
        
        virtual std::string getPersonalDescription() const;
        
        virtual Vampire* clone() const;
        
    protected:
        virtual Character * getRandomTarget(std::function<bool(Character*)> = [](Character *){return true;}) const;
        virtual Attack performAttack(Character * defender, std::string attackType);
        std::string getAttackType() const;
    };
}

#endif
