#ifndef __cprog13_game__Character__
#define __cprog13_game__Character__

#include "PhysicalObject.h"

namespace game {
    class Item;
    class Backpack;
    class Container;
    
    class Character : public PhysicalObject {
        unsigned int health;
        const unsigned int maxHealth;
        bool alive;
        Environment * env;
        Backpack * inventory;
        unsigned int rottenness;
        
    public:
        struct Attack {
            unsigned int health;
            std::string description;
            
            explicit Attack(unsigned int health);
            Attack(unsigned int health, std::string description);
        };
        
        Character(Environment * env, std::string subType, unsigned int maxHealth);
        Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize);
        Character(const Character & character);
        Character(Character && character);
        virtual ~Character();
        
        Environment * getEnvironment() const;
        Backpack * getInventory() const;
        
        std::string getName() const;
        
        bool move(Environment * from, Environment * to);
        bool move(const std::string & direction);
        
        void dropInventory();
        bool pickItem(const Item * item);
        bool pickItem(const Item * item, Container * con);
        bool dropItem(const Item * item);
        bool putItem(const Item * item, Container * con);
        
        unsigned int getMaxHealth() const;
        unsigned int getHealth() const;
        
        bool isAlive() const;
        virtual void kill();
        
        unsigned int getRottenness() const;
        
        virtual void update();
        
        virtual void interact(Character * other) = 0;
        Attack attack(const Character * attacker, unsigned int health);
        Attack attack(const Character * attacker, unsigned int health, std::string description);
        virtual Attack attack(const Character * attacker, const Attack & attack) = 0;
        
    protected:
        void setHealth(unsigned int health);
        void incHealth(unsigned int health);
        void decHealth(unsigned int health);
        void addHealth(int health);
        
        virtual std::string getPersonalDescription() const;
        virtual std::string getStatisticalDescription() const;
    };
}

#endif