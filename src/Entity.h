#ifndef __cprog13_game__Entity__
#define __cprog13_game__Entity__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include "PhysicalObject.h"
#include <string>
#include <vector>


namespace game {
    class Environment;
    class Backpack;
    class Item;
    
    class Entity : public PhysicalObject {
        bool alive;
        Environment * env;
        Backpack * inventory;
        
    public:
        Entity(Environment * env, std::string type);
        Entity(Environment * env, std::string type, bool visible, int inventorySize);
        Entity(const Entity & entity);
        Entity(Entity && entity);
        virtual ~Entity();
        
        Environment * getEnvironment() const;
        Backpack * getInventory() const;
        
        bool move(Environment * from, Environment * to);
        bool move(const std::string & direction);
        
        void dropInventory();
        bool pickItem(const Item * item);
        bool dropItem(const Item * item);
        
        bool isAlive() const;
        virtual void kill();
        
        virtual void update() = 0;
    };
}

#endif
