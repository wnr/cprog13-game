#ifndef __cprog13_game__Item__
#define __cprog13_game__Item__

#include <string>
#include <vector>

#include "Object.h"

namespace game {
    
    class Item : public Object {
        unsigned int volume;
    public:
        //TODO: type is last parameter for all other objects. Why not volume in constructor?
        Item(std::string type);
        Item(std::string type, bool visible);
        Item(const Item & item);
        Item(Item && item);
        virtual ~Item();
        
        unsigned int getVolume() const;
        
        virtual std::string toString() const;
        virtual std::string getDescription() const;
    };
}

//TODO: check if this is a good way to do it.
int operator+=(int, const game::Item &);
int operator+(const game::Item &, const game::Item &);
bool operator<(int, const game::Item &);


#endif