#ifndef __cprog13_game__Item__
#define __cprog13_game__Item__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include <string>
#include <vector>

#include "Loggable.h"
#include "Object.h"

namespace game {
    
    class Item : public Object {
    protected:
        std::string type;
        bool visible;
        bool breakable;
        bool working;
    public:
        Item(Engine * engine, std::string type);
        Item(Engine * engine, std::string type, bool visible, bool breakable);
        Item(Engine * engine, std::string type, bool visible, bool breakable, bool working);
        Item(const Item & item);
        Item(Item && item);
        ~Item();
        
        std::string getType() const;
        bool isVisible() const;
        bool isBreakable() const;
        bool isWorking() const;
        
        virtual bool breakItem();
        
        virtual std::string toString() const;
        virtual std::string getDescription() const;
    };
}

#endif
