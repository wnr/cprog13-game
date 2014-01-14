#ifndef __cprog13_game__Item__
#define __cprog13_game__Item__

#include <string>
#include <vector>

#include "Object.h"

namespace game {
    
    class Item : public Object {
    protected:
        bool breakable; //TODO: Might do different class from this and working.
        bool working;
        int volume;
    public:
        Item(std::string type);
        Item(std::string type, bool visible, bool breakable);
        Item(std::string type, bool visible, bool breakable, bool working);
        Item(const Item & item);
        Item(Item && item);
        virtual ~Item();
        
        std::string getType() const;
        bool isVisible() const;
        bool isBreakable() const;
        bool isWorking() const;
        int getVolume() const;
        
        virtual bool breakItem();
        
        virtual std::string toString() const;
        virtual std::string getDescription() const;
    };
}

int operator+=(int, const game::Item &);
int operator+(const game::Item &, const game::Item &);

#endif
