#ifndef __cprog13_game__PhysicalObject__
#define __cprog13_game__PhysicalObject__

//An Object can be anything that can exist in an Environment, either directly or indirectly (objects carried by some Entity).

#include <string>

#include "BaseObject.h"


namespace game {
    
    class Engine;
    class Environment;
    class Item;
    
    class PhysicalObject : public BaseObject {
        bool visible;
        
    public:
        PhysicalObject(std::string mainType, std::string subType);
        PhysicalObject(std::string mainType, std::string subType, bool visible);
        PhysicalObject(const PhysicalObject & pObject);
        PhysicalObject(PhysicalObject && pObject);
        virtual ~PhysicalObject();
        
        bool isVisible() const;
        bool isContainer() const;
        bool isEntity() const;
        bool isItem() const;
        
        virtual void update(); //TODO: Make pure virtual.
        
        virtual std::string getDescription() const = 0;
    };
}

#endif