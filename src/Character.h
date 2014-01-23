#ifndef __cprog13_game__Character__
#define __cprog13_game__Character__

#include "PhysicalObject.h"

namespace game {
    class Item;
    class Backpack;
    class Container;
    class Food;
    class Equipment;
    class BreakableItem;
    
    class Character : public PhysicalObject {
        unsigned int health;
        const unsigned int maxHealth;
        bool alive;
        Environment * env;
        Backpack * inventory;
        Equipment * equipment;
        unsigned int rottenness;
        bool interacting;
        
    public:
        struct Attack {
            unsigned int health;
            std::string description;
            
            explicit Attack(unsigned int health);
            Attack(unsigned int health, std::string description);
        };
        
        //When a Character is constructed, it will add itself to the given environment.
        Character(Environment * env, std::string subType, unsigned int maxHealth);
        Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize);
        Character(const Character & character);
        Character(Character && character);
        virtual ~Character();
        
        Environment * getEnvironment() const;
        Equipment * getEquipment() const;
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
        
        bool isInteracting() const;
        
        bool isAlive() const;
        virtual void kill();
        
        unsigned int getRottenness() const;
        
        virtual void update();
        
        virtual bool startInteraction(Character * other);
        virtual void endInteraction(Character * other);
        virtual void interact(Character * other) = 0;
        
        Attack attack(const Character * attacker, unsigned int health);
        Attack attack(const Character * attacker, unsigned int health, std::string description);
        virtual Attack attack(const Character * attacker, const Attack & attack);

        bool eatFood(Food * food);
        
    protected:
        void setHealth(unsigned int health);
        void incHealth(unsigned int health);
        void decHealth(unsigned int health);
        void addHealth(int health);
        
        unsigned int getAttackPower() const;
        unsigned int getArmorRating() const;
        unsigned int getDodgeProb() const;
        unsigned int getBlockProb() const;
        
        virtual unsigned int getBaseArmorRating() const;
        virtual unsigned int getBaseAttackPower() const;
        virtual unsigned int getBaseDodgeProb() const;
        virtual unsigned int getBaseBlockProb() const;
        
        virtual unsigned int dodgeMod(const unsigned int originalDmg) const;
        virtual unsigned int blockMod(const unsigned int originalDmg) const;
        virtual unsigned int armorMod(const unsigned int originalDmg) const;
        
        virtual void affectDurability(BreakableItem * bi, unsigned int power) const = 0;
        
        virtual std::string getPersonalDescription() const;
        virtual std::string getStatisticalDescription() const;
        
        virtual bool equip(const BreakableItem * bItem);
        virtual bool unEquip(const BreakableItem * bItem);
    };
}

#endif