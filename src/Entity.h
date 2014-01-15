#ifndef __cprog13_game__Entity__
#define __cprog13_game__Entity__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include <string>
#include <vector>

#include "Object.h"

namespace game {
    class Engine;
    class Environment;
    
    class Entity : public Object {
        bool alive;
        
    public:
        Entity(std::string type);
        Entity(std::string type, bool visible);
        Entity(const Entity & entity);
        Entity(Entity && entity);
        virtual ~Entity();
        
        bool move(Environment & env, const std::string & direction);
        
        bool isAlive() const;
        virtual void kill();
        
        virtual void update(Environment &) = 0;
    };
}

#endif
