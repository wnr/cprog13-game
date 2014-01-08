#ifndef __cprog13_game__Entity__
#define __cprog13_game__Entity__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include <string>
#include <vector>

namespace game {
    class Engine;
    
    class Entity {
        std::string type;
        bool alive;
        Engine * engine;
        
    public:
        Entity(Engine * engine, std::string type);
        Entity(const Entity & entity);
        Entity(Entity && entity);
        ~Entity();
        
        virtual void update() = 0;
        
        std::string getType() const;
        bool isAlive() const;
        void kill();
    };
}

#endif
