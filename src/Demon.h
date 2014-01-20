#ifndef __cprog13_game__Demon__
#define __cprog13_game__Demon__

#include "Monster.h"

namespace game {
    class Demon : public Monster {
    public:
        Demon(Environment * env);
        Demon(Environment * env, std::string name, unsigned int maxHealth);
        Demon(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb);
        Demon(const Demon & monster);
        Demon(Demon && monster);
        virtual ~Demon();
        
        virtual void interact(Character * other);
        virtual Attack attack(const Character * attacker, const Attack & attack);
    };
}

#endif
