#ifndef __cprog13_game__Environment__
#define __cprog13_game__Environment__

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "BaseObject.h"
#include "GameStorage.h"
#include "PhysicalObject.h"

//Environment describes a place where Objects can be. All environments makes the game world.
//Environment handles and owns all Objects that are in them. Environments moves the ownership between them when
//for example an Entity moves between Environments. Environments keeps track of the neighbors with pointers.

namespace game {
    class PhysicalObject;
    class Entity;
    
    class Environment : public BaseObject, public GameStorage<PhysicalObject> {
        std::string name;
        std::string description;
        std::map<std::string, Environment* > neighbors;
        
    public:
        Environment(std::string name, std::string desc);
        Environment(std::string subType, std::string name, std::string desc);
        Environment(const Environment & env);
        Environment(Environment && env);
        virtual ~Environment();
        
        void setNeightbor(std::string direction, Environment * env);
        
        //Returns NULL if no neighbor is found in that direction.
        //is case insensitive.
        Environment * getNeighbor(const std::string & direction);
        
        std::string getName() const;
        std::string getDescription() const;
        std::string getFullInfo() const;
        std::vector<std::string> getDirections() const;
        
        virtual void updateObjects();
        virtual void update();
        
        virtual std::string toString() const;
    };
}

#endif
