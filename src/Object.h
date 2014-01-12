#ifndef __cprog13_game__Entity__
#define __cprog13_game__Entity__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include <string>
#include <vector>

#include "Loggable.h"

namespace game {
    class Environment;
    class Entity;
    
    class Object : public Loggable {
    protected:
        std::string type;
        bool visible;
        Environment * env;
    public:
        Object(std::string type, bool visible);
        Object(const Object & object);
        Object(Object && object);
        ~Object();
        
        virtual void update() = 0;
        
        std::string getType() const;
        bool isVisible();
        virtual bool destroy();
        
        void setEnvironment(Environment * env);
        
        virtual std::string toString() const;
        virtual std::string getDescription() const = 0;
    };
}

#endif
