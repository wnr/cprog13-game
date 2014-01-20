#ifndef __cprog13_game__Ghost__
#define __cprog13_game__Ghost__

#include "Monster.h"

namespace game {
    class Environment;
    
    class Ghost : public Monster {
    public:
        Ghost(Environment * env);
        Ghost(Environment * env, std::string name, unsigned int maxHealth);
        Ghost(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb);
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
    };
}

#endif
