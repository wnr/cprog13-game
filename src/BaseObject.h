#ifndef __cprog13_game__BaseObject__
#define __cprog13_game__BaseObject__

//An Object can be anything that can exist in an Environment, either directly or indirectly (objects carried by some Entity).

#include <string>

#include "Loggable.h"

namespace game {
    
    class Engine;
    
    class BaseObject : public Loggable {
        std::string mainType;
        std::string subType;
        bool tickSync;
        
    public:
        BaseObject(std::string mainType, std::string subType);
        BaseObject(const BaseObject & baseObject);
        BaseObject(BaseObject && baseObject);
        virtual ~BaseObject();
        
        std::string getMainType() const;
        std::string getSubType() const;
        
        virtual std::string toString() const;
        
        virtual std::string getDescription() const = 0;
        
        Engine & getEngine() const;
        
        virtual void update();
        
        bool getTickSync() const;
        void setTickSync(bool ts);
        void tick();
    };
}

#endif