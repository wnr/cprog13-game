#ifndef __cprog13_game__Object__
#define __cprog13_game__Object__

//An Object can be anything that can exist in an Environment, either directly or indirectly (objects carried by some Entity).

#include <string>

#include "Loggable.h"
#include "Environment.h"

namespace game {
    
    class Engine;
    
    class Object : public Loggable {
        std::string type;
        bool visible;
        Environment * env;
        
    public:
        Object(std::string type);
        Object(std::string type, bool visible);
        Object(const Object & object);
        Object(Object && object);
        virtual ~Object();
        
        std::string getType() const;
        bool isVisible() const;
        Engine & getEngine() const;
        
        void setEnvironment(Environment * env);
        Environment * getEnvironment() const;
        bool move(const std::string & direction);
        
        virtual std::string toString() const;
        virtual void update(const Environment & env);
        virtual std::string getDescription() const = 0;
    };
}

#endif