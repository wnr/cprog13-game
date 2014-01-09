#ifndef __cprog13_game__Character__
#define __cprog13_game__Character__

#include "Entity.h"

namespace game {
    class Entity;
    
    class Character : public Entity {
        unsigned int health;
        const unsigned int maxHealth;
        const std::string name;
        
    public:
        Character(Engine * engine, int maxHealth, std::string name);
        Character(Engine * engine, int maxHealth, std::string name, std::string type);
        Character(const Character & character);
        Character(Character && character);
        ~Character();
        
        unsigned int getMaxHealth() const;
        
        unsigned int getHealth() const;
        void setHealth(unsigned int health);
        void incHealth(unsigned int health);
        void decHealth(unsigned int health);
        void addHealth(int health);
        
        std::string getName() const;
        
        virtual void kill();
        
        virtual std::string toString() const;
    };
}

#endif
