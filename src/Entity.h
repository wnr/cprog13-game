#ifndef __cprog13_game__Entity__
#define __cprog13_game__Entity__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include <string>
#include <vector>

#include "Loggable.h"

namespace game {
    class Engine;
    class Environment;
    
    class Entity : public Loggable {
    protected:
        std::string type;
        bool alive;
        Engine * engine;
        Environment * env;
        
    public:
        Entity(Engine * engine, std::string type);
        Entity(const Entity & entity);
        Entity(Entity && entity);
        ~Entity();
        
        virtual void update(const Environment & env) = 0;
        
        std::string getType() const;
        bool isAlive() const;
        virtual void kill();
        
        void setEnvironment(Environment * env);
        bool move(const std::string & direction);
        
        virtual std::string toString() const;
        virtual std::string getDescription() const = 0;
    };
}

#endif