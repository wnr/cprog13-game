#ifndef __cprog13_game__DemonBoss__
#define __cprog13_game__DemonBoss__

#include "Demon.h"

namespace game {
    class DemonBoss : public Demon {
    public:
        DemonBoss(Environment * env);
        DemonBoss(Environment * env, std::string subType, unsigned int maxHealth);
        DemonBoss(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        DemonBoss(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb);
        DemonBoss(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod);
        DemonBoss(const DemonBoss & demonBoss);
        DemonBoss(DemonBoss && demonBoss);
        virtual ~DemonBoss();
        
        virtual void interact(Character * other);
        virtual Attack attack(const Character * attacker, const Attack & attack);
        
        virtual DemonBoss* clone() const;
        
    protected:
        virtual std::string getAttackType() const;
        virtual std::string getPersonalDescription() const;
    };
}

#endif
