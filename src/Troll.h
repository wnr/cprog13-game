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
        Troll(const Troll & troll);
        Troll(Troll && troll);
        virtual ~Troll();
        
        virtual void update();
        
        virtual void interact(Character * other);
        virtual Attack attack(const Character * attacker, const Attack & attack);
    };
}

#endif
