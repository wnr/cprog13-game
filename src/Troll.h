#ifndef __cprog13_game__Troll__
#define __cprog13_game__Troll__

#include "Monster.h"

namespace game {
    class Troll : public Monster {
    public:
        
        Troll(Environment * env);
        Troll(Environment * env, std::string subType, unsigned int maxHealth);
        Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb);
        Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod);
        Troll(const Troll & troll);
        Troll(Troll && troll);
        virtual ~Troll();
        
        virtual Troll* clone() const;
        
    protected:
        virtual std::string getAttackType() const;
        virtual std::string getPersonalDescription() const;
    };
}

#endif
