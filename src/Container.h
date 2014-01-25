#ifndef __cprog13_game__Container__
#define __cprog13_game__Container__

#include <string>
#include <vector>

#include "PhysicalObject.h"
#include "GameStorage.h"
#include "Item.h"

namespace game {
    
    class Engine;
    
    class Container : public PhysicalObject, public GameStorage<Item> {
        const unsigned int maxSize;
    public:
        Container(std::string subType, unsigned int maxSize);
        Container(std::string subType, unsigned int maxSize, std::string name);
        Container(const Container & container);
        Container(Container && container);
        virtual ~Container();

        unsigned int getMaxSize() const;
        virtual int getRemainingSpace() const;
        virtual int getTakenSpace() const;
        virtual std::unique_ptr<Item> push_back(std::unique_ptr<Item> item);
        
        virtual void update();
        virtual std::string getDescription() const;
        
        virtual Container* clone() const;
        
    protected:
        virtual std::string getPersonalDescription() const;
        virtual std::string getStatisticalDescription() const;
    };
}

#endif
