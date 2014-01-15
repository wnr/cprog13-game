#ifndef __cprog13_game__Object__
#define __cprog13_game__Object__

//An Object can be anything that can exist in an Environment, either directly or indirectly (objects carried by some Entity).

#include <string>

#include "Loggable.h"

namespace game {
    
    class Engine;
    
    class Object : public Loggable {
        std::string type;
        bool visible;
        bool carriable; //TODO: Might wanna have this as a class.
        
    public:
        Object(std::string type);
        Object(std::string type, bool visible, bool carriable);
        Object(const Object & object);
        Object(Object && object);
        virtual ~Object();
        
        std::string getType() const;
        bool isVisible() const;
        bool isCarriable() const;
        Engine & getEngine() const;
        
        virtual std::string toString() const;
        virtual std::string getDescription() const = 0;
    };
}

#endif