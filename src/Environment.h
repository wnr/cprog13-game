#ifndef __cprog13_game__Environment__
#define __cprog13_game__Environment__

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "Loggable.h"
#include "OwningVector.h"

//Environment describes a place where Objects can be. All environments makes the game world.
//Environment handles and owns all Objects that are in them. Environments moves the ownership between them when
//for example an Entity moves between Environments. Environments keeps track of the neighbors with weak pointers to break cyclic dependencies
//between Engine and Environment.

namespace game {
    class Object;
    class Entity;
    
    class Environment : public Loggable, private OwningVector<Object> {
        std::string description;
        std::map<std::string, Environment* > neighbors; //TODO: Weak pointers? Don´t we have normal pointers here?
        
    public:
        Environment(std::string desc);
        Environment(const Environment & env);
        Environment(Environment && env);
        virtual ~Environment();
        
        using OwningVector<Object>::for_each;
        using OwningVector<Object>::size;
        
        void setNeightbor(std::string direction, Environment * env);
        
        //Returns NULL if no neighbor is found in that direction.
        Environment * getNeighbor(const std::string & direction);
        
        std::string getDescription() const;
        std::vector<std::string> getDirections() const;
        
        //Transfers the ownership of the object to the Environment.
        void addObject(std::unique_ptr<Object> obj);
        
        //Removes the entity from this envrionment and transfers the ownership to the caller.
        //After this is done Entity will not belong to any Environment.
        //TODO: So entities can be free? Aka temporarely not belong to any Environment? Sounds like thats impossible by the class description.
        std::unique_ptr<Object> removeObject(Object * obj);
        
        virtual void updateObjects();
        virtual void update();
        
        virtual std::string toString() const;
    };
}

#endif
