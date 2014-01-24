#ifndef __cprog13_game__Monster__
#define __cprog13_game__Monster__

#include "Character.h"

namespace game {
    class Monster : public Character {
        float moveProb;
        float attackProb;
        
    public:
        Monster(Environment * env, std::string subType, unsigned int maxHealth);
        Monster(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Monster(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb);
        Monster(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod);
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
        
        Attack attack(const Character * attacker, const Attack & attack);
        void affectDurability(BreakableItem * bi, unsigned int power) const;
        
        virtual void update();
    };
}

#endif
