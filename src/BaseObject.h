#ifndef __cprog13_game__BaseObject__
#define __cprog13_game__BaseObject__

//An Object can be anything that can exist in an Environment, either directly or indirectly (objects carried by some Entity).

#include <string>

namespace game {
    
    class Engine;
    
    class BaseObject {
        std::string mainType;
        std::string subType;
        std::string name;
        bool tickSync;
        
    public:
        BaseObject(std::string mainType, std::string subType);
        BaseObject(std::string mainType, std::string subType, std::string name);
        BaseObject(const BaseObject & baseObject);
        BaseObject(BaseObject && baseObject);
        virtual ~BaseObject();
        
        std::string getMainType() const;
        std::string getSubType() const;
        
        virtual std::string toString() const;
        
        virtual std::string getDescription() const = 0;
        
        virtual std::string getName() const;
        
        Engine * getEngine() const;
        
        virtual void update();
        
        bool getTickSync() const;
        void setTickSync(bool ts);
        void tick();
    };
}

#endif