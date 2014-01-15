#ifndef __cprog13_game__Item__
#define __cprog13_game__Item__

#include <string>
#include <vector>

#include "Object.h"

namespace game {
    
    class Item : public Object {
        bool breakable; //TODO: Might do different class from this and working.
        bool working;
        unsigned int volume;
    public:
        //TODO: type is last parameter for all other objects. Why not volume in constructor?
        Item(std::string type);
        Item(std::string type, bool visible, bool breakable);
        Item(std::string type, bool visible, bool breakable, bool working);
        Item(const Item & item);
        Item(Item && item);
        virtual ~Item();
        
        bool isBreakable() const;
        bool isWorking() const;
        unsigned int getVolume() const;
        
        virtual bool breakItem();
        
        virtual std::string toString() const;
        virtual std::string getDescription() const;
    };
}

//TODO: check if this is a good way to do it.
int operator+=(int, const game::Item &);
int operator+(const game::Item &, const game::Item &);

#endif
