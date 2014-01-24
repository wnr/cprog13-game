#ifndef __cprog13_game__PhysicalObject__
#define __cprog13_game__PhysicalObject__

//An Object can be anything that can exist in an Environment, either directly or indirectly (objects carried by some Character).

#include <string>

#include "BaseObject.h"


namespace game {
    
    class Engine;
    class Environment;
    class Item;
    
    class PhysicalObject : public BaseObject {
        
    public:
        PhysicalObject(std::string mainType, std::string subType);
        PhysicalObject(std::string mainType, std::string subType, std::string name);
        PhysicalObject(const PhysicalObject & pObject);
        PhysicalObject(PhysicalObject && pObject);
        virtual ~PhysicalObject();
        
        bool isContainer() const;
        bool isCharacter() const;
        bool isItem() const;
        
        virtual std::string getDescription() const;
        virtual PhysicalObject* clone() const = 0;
        
    protected:
        virtual std::string getPersonalDescription() const;
        virtual std::string getStatisticalDescription() const = 0;
    };
}

#endif