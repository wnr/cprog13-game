#ifndef __cprog13_game__Monster__
#define __cprog13_game__Monster__

#include "Character.h"

namespace game {
    class Monster : public Character {
        float moveProb;
        float attackProb;
        
    public:
        Monster(Environment * env, std::string name, unsigned int maxHealth);
        Monster(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb);
        Monster(const Monster & monster);
        Monster(Monster && monster);
        virtual ~Monster();
        
        float getMoveProb() const;
        void setMoveProb(float prob);
        void addMoveProb(float prob);
        void incMoveProb(float prob);
        void decMoveProb(float prob);
        
        float getAttackProb() const;
        void setAttackProb(float prob);
        void addAttackProb(float prob);
        void incAttackProb(float prob);
        void decAttackProb(float prob);
        
        virtual void update();
    };
}

#endif
