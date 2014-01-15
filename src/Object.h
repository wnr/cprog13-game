#ifndef __cprog13_game__Object__
#define __cprog13_game__Object__

//An Object can be anything that can exist in an Environment, either directly or indirectly (objects carried by some Entity).

#include <string>

#include "Loggable.h"
#include "Environment.h"
#include "Constants.h"

namespace game {
    
    class Engine;
    
    class Object : public Loggable {
        std::string mainType;
        std::string subType;
        bool visible;
        
    public:
        Object(std::string mainType, std::string subType);
        Object(std::string mainType, std::string subType, bool visible);
        Object(const Object & object);
        Object(Object && object);
        virtual ~Object();
        
        bool isVisible() const;
        bool isContainer() const;
        bool isEntity() const;
        bool isItem() const;
        
        std::string getMainType() const;
        std::string getSubType() const;
        
        virtual void update(Environment & env);
        
        virtual std::string toString() const;
        
        virtual std::string getDescription() const = 0;
        
        Engine & getEngine() const;
    };
}

#endif