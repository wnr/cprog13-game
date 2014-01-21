#ifndef __cprog13_game__Demon__
#define __cprog13_game__Demon__

#include "Monster.h"

namespace game {
    class Demon : public Monster {
    public:
        Demon(Environment * env);
        Demon(Environment * env, std::string subType, unsigned int maxHealth);
        Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Demon(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb);
        Demon(const Demon & demon);
        Demon(Demon && demon);
        virtual ~Demon();
        
        virtual void interact(Character * other);
        virtual Attack attack(const Character * attacker, const Attack & attack);
    };
}

#endif
