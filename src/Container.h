#ifndef __cprog13_game__Container__
#define __cprog13_game__Container__

//An Entity is something that lives in the game world and interacts with other entities or environments in
//some way. A monster is an Entity and a player is an Entity. However, items and environments are not Entities.
//Entities can be viewed as "living things" that can perform actions independently of the player.

#include <string>
#include <vector>

namespace game {
    
    class Engine;
    
    class Inventory : public Object {
    protected:
        list
        const int maxSize;
    public:
        Container();
        Container(const Inventory & inv);
        Container(Inventory && inv);
        ~Container();
    
        std::string toString() const;
    };
}

#endif
