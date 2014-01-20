#ifndef __cprog13_game__Troll__
#define __cprog13_game__Troll__

#include "Monster.h"

namespace game {
    class Troll : public Monster {
    public:
        
        Troll(Environment * env);
        Troll(Environment * env, std::string name, unsigned int maxHealth);
        Troll(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb);
        Troll(const Monster & monster);
        Troll(Monster && monster);
        virtual ~Troll();
        
        
        virtual void interact(Character * other);
        virtual Attack attack(const Character * attacker, const Attack & attack);
    };
}

#endif
