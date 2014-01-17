#ifndef __cprog13_game__Environment__
#define __cprog13_game__Environment__

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "Loggable.h"
#include "OwningStorage.h"
#include "BaseObject.h"
#include "PhysicalObject.h"

//Environment describes a place where Objects can be. All environments makes the game world.
//Environment handles and owns all Objects that are in them. Environments moves the ownership between them when
//for example an Entity moves between Environments. Environments keeps track of the neighbors with pointers.

namespace game {
    class PhysicalObject;
    class Entity;
    
    class Environment : public BaseObject, private OwningStorage<PhysicalObject> {
        std::string name;
        std::string description;
        std::map<std::string, Environment* > neighbors;
        
    public:
        Environment(std::string name, std::string desc);
        Environment(std::string subType, std::string name, std::string desc);
        Environment(const Environment & env);
        Environment(Environment && env);
        virtual ~Environment();
        
        using OwningStorage<PhysicalObject>::for_each;
        using OwningStorage<PhysicalObject>::size;
        
        void setNeightbor(std::string direction, Environment * env);
        
        //Returns NULL if no neighbor is found in that direction.
        Environment * getNeighbor(const std::string & direction);
        
        std::string getName() const;
        std::string getDescription() const;
        std::string getFullInfo() const;
        std::vector<std::string> getDirections() const;
        
        //Transfers the ownership of the object to the Environment.
        void addObject(std::unique_ptr<PhysicalObject> obj);
        
        //Removes the entity from this envrionment and transfers the ownership to the caller.
        //After this is done Entity will not belong to any Environment.
        //TODO: So entities can be free? Aka temporarely not belong to any Environment? Sounds like thats impossible by the class description.
        std::unique_ptr<PhysicalObject> removeObject(PhysicalObject * obj);
        
        virtual void updateObjects();
        virtual void update();
        
        virtual std::string toString() const;
    };
}

#endif
