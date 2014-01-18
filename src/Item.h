#ifndef __cprog13_game__Item__
#define __cprog13_game__Item__

#include <string>
#include <vector>

#include "PhysicalObject.h"
#include "OwningStorage.h"
#include "Constants.h"

namespace game {
    
    class Item : public PhysicalObject {
        unsigned int volume;
    public:
        //TODO: type is last parameter for all other objects. Why not volume in constructor?
        Item(std::string type);
        Item(std::string type, bool visible);
        Item(const Item & item);
        Item(Item && item);
        virtual ~Item();
        
        unsigned int getVolume() const;
        
        virtual std::string getDescription() const;
        
        template<class T, class E>
        bool move(OwningStorage<T> * from, OwningStorage<E> * to) const {
            to->push_back(from->template remove<E>(this));
            return true;
        }
    };
}

//TODO: check if this is a good way to do it.
int operator+=(int, const game::Item &);
int operator+(const game::Item &, const game::Item &);
bool operator<(int, const game::Item &);


#endif