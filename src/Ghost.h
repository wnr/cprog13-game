#ifndef __cprog13_game__Ghost__
#define __cprog13_game__Ghost__

#include "Monster.h"

namespace game {
    class Environment;
    
    class Ghost : public Monster {
    public:
        Ghost(Environment * env);
        Ghost(Environment * env, std::string subType, unsigned int maxHealth);
        Ghost(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Ghost(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb);
        Ghost(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod);
        Ghost(const Ghost & ghost);
        Ghost(Ghost && ghost);
        virtual ~Ghost();
        
        //Ghost will remove itself from env when killed directly. No rottenness.
        virtual void kill();
//
//        virtual void update();
//        virtual void interact();
//        virtual unsigned int attack(unsigned int hp);
        //virtual void update();
        
        virtual void interact(Character * other);
        virtual Attack attack(const Character * attacker, const Attack & attack);
        
        virtual std::string getPersonalDescription() const;
        
        virtual Ghost* clone() const;
    };
}

#endif
