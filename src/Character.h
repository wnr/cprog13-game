#ifndef __cprog13_game__Character__
#define __cprog13_game__Character__

#include "Entity.h"

namespace game {
    class Entity;
    class Item;
    
    class Character : public Entity {
        unsigned int health;
        const unsigned int maxHealth;
    public:
        struct Attack {
            unsigned int health;
            std::string description;
            
            explicit Attack(unsigned int health);
            Attack(unsigned int health, std::string description);
        };
        
        Character(Environment * env, std::string name, unsigned int maxHealth);
        Character(Environment * env, std::string name, unsigned int maxHealth, std::string subType);
        Character(const Character & character);
        Character(Character && character);
        virtual ~Character();
        
        unsigned int getMaxHealth() const;
        
        unsigned int getHealth() const;
        
        virtual void kill();
        
        virtual std::string getDescription() const;
        
        virtual void interact(Character * other) = 0;
        Attack attack(const Character * attacker, unsigned int health);
        Attack attack(const Character * attacker, unsigned int health, std::string description);
        virtual Attack attack(const Character * attacker, const Attack & attack) = 0;
        
    protected:
        void setHealth(unsigned int health);
        void incHealth(unsigned int health);
        void decHealth(unsigned int health);
        void addHealth(int health);
    };
}

#endif
