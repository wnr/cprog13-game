#ifndef __cprog13_game__Item__
#define __cprog13_game__Item__

#include <string>
#include <vector>

#include "PhysicalObject.h"
#include "GameStorage.h"
#include "Constants.h"

namespace game {
    
    class Item : public PhysicalObject {
        unsigned int weight;
    public:
        //TODO: type is last parameter for all other objects. Why not weight in constructor?
        Item(std::string subType, unsigned int weight);
        Item(std::string subType, unsigned int weight, std::string name);
        Item(const Item & item);
        Item(Item && item);
        virtual ~Item();
        
        unsigned int getWeight() const;
        
        virtual void update();
        
        template<class T, class E>
        bool move(GameStorage<T> * from, GameStorage<E> * to) const {
            auto uniqueItem(from->template remove<E>(this));
            if(uniqueItem == nullptr) {
                return false;
            }
            uniqueItem = to->push_back(std::move(uniqueItem));
            if(uniqueItem != nullptr) {
                if(from->push_back(std::unique_ptr<T>((T*)(uniqueItem.release()))) != nullptr) {
                    throw std::runtime_error("We failed to make a container switch and then failed to restore to item.");
                }
                return false;
            }
            return true;
        }
    protected:
        virtual std::string getPersonalDescription() const;
        virtual std::string getStatisticalDescription() const;
    };
}

//TODO: check if this is a good way to do it.
int operator+=(int &, const game::Item &);
int operator+(const game::Item &, const game::Item &);
bool operator<(int, const game::Item &);


#endif