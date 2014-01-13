#ifndef __cprog13_game__Character__
#define __cprog13_game__Character__

#include "Entity.h"
//#include "Inventory.h"

namespace game {
    class Entity;
    class Item;
    
    class Character : public Entity {
        unsigned int health;
        const unsigned int maxHealth;
        const std::string name;
//        Inventory * inventory;
    public:
        Character(std::string name, int maxHealth);
        Character(std::string name, int maxHealth, std::string type);
        Character(const Character & character);
        Character(Character && character);
        virtual ~Character();
        
        unsigned int getMaxHealth() const;
        
        unsigned int getHealth() const;
        void setHealth(unsigned int health);
        void incHealth(unsigned int health);
        void decHealth(unsigned int health);
        void addHealth(int health);
//        void dropInventory();
//        bool pickItem(Item * item);
//        void dropItem(Item * item);
        
        std::string getName() const;
        
        virtual void kill();
        
        virtual std::string toString() const;
        virtual std::string getDescription() const;
    };
}

#endif
