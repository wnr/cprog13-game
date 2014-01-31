#ifndef __cprog13_game__Character__
#define __cprog13_game__Character__

#include "PhysicalObject.h"
#include "Food.h"
#include "Potion.h"

namespace game {
    class Item;
    class Inventory;
    class Container;
    class Food;
    class Equipment;
    class BreakableItem;
    
    class Character : public PhysicalObject {
        unsigned int health;
        unsigned int maxHealth;
        unsigned int baseArmorRating;
        unsigned int baseDodgeProb;
        unsigned int baseBlockProb;
        unsigned int baseMinDmg;
        unsigned int baseMaxDmg;
        unsigned int baseCritProb;
        unsigned int baseCritMod;
        bool alive;
        Environment * env;
        std::unique_ptr<Inventory> inventory;
        std::unique_ptr<Equipment> equipment;
        unsigned int rottenness;
        bool interacting;
        
    public:
        struct Attack {
            unsigned int health;
            std::string type;
            std::function<std::string (unsigned int health)> specialDescription;
            
            explicit Attack(unsigned int health);
            Attack(unsigned int health, std::string type);
            Attack(unsigned int health, std::string type, std::function<std::string (unsigned int health)> specialDescription);
            
        };
        friend void Food::incHealth(unsigned int health, Character * character) const;
        friend void Potion::addMaxHealth(unsigned int health, Character * character) const;
        
        //When a Character is constructed, it will add itself to the given environment.
        Character(Environment * env, std::string subType);
        Character(Environment * env, std::string subType, unsigned int maxHealth);
        Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name);
        Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize);
        Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod);
        Character(const Character & character);
        Character(Character && character);
        virtual ~Character();
        
        Environment * getEnvironment() const;
        Equipment * getEquipment() const;
        Inventory * getInventory() const;
        
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
        void setRottenness(unsigned int rottenness);
        
        virtual void update();
        
        virtual bool startInteraction(Character * other);
        virtual void endInteraction(Character * other);
        virtual void interact(Character * other) = 0;
        
        Attack attack(Character * attacker, unsigned int health);
        Attack attack(Character * attacker, unsigned int health, std::string description);
        virtual Attack attack(Character * attacker, const Attack & attack);
        virtual Attack afterDefence(Character * defender, const Attack & effect);
        virtual Attack afterOffence(Character * attacker, const Attack & effect);
        
        virtual void setEnvironment(Environment*);
        
    protected:
        Attack generateAttack(std::string attackType) const;
        virtual Attack performAttack(Character * defender, std::string attackType);
        virtual Character * getRandomTarget(std::function<bool(Character*)> = [](Character *){return true;}) const;
        
        void incHealth(unsigned int health);
        void decHealth(unsigned int health);
        void setHealth(unsigned int health);
        void addHealth(int health);
        void addMaxHealth(int health);
        void setMaxHealth(unsigned int health);
        
        unsigned int getAttackPower() const;
        unsigned int getMinDmg() const;
        unsigned int getMaxDmg() const;
        unsigned int getArmorRating() const;
        unsigned int getDodgeProb() const;
        unsigned int getBlockProb() const;
        unsigned int getCritProb() const;
        unsigned int getCritMod() const;
        
        virtual unsigned int getBaseArmorRating() const;
        virtual unsigned int getBaseMinDmg() const;
        virtual unsigned int getBaseMaxDmg() const;
        virtual unsigned int getBaseDodgeProb() const;
        virtual unsigned int getBaseBlockProb() const;
        virtual unsigned int getBaseCritProb() const;
        virtual unsigned int getBaseCritMod() const;
        
        virtual unsigned int dodgeMod(const unsigned int originalDmg) const;
        virtual unsigned int blockMod(const unsigned int originalDmg) const;
        virtual unsigned int armorMod(const unsigned int originalDmg) const;
        
        virtual bool isCriticalHit(unsigned int & attackPower) const;
        
        virtual void affectDurability(BreakableItem * bi, unsigned int power) const = 0;
        
        virtual std::string getPersonalDescription() const;
        virtual std::string getStatisticalDescription() const;
        
        virtual bool equip(const BreakableItem * bItem);
        virtual bool unEquip(const BreakableItem * bItem);
    };
}

#endif