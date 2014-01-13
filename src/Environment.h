#ifndef __cprog13_game__Environment__
#define __cprog13_game__Environment__

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "Loggable.h"

//Environment describes a place where entities can be. All environments makes the game world.
//Environment handles and owns all Entities that are in them. Environments moves the ownership between them when
//an Entity moves between Environments. Environments keeps track of the neighbors with weak pointers to break cyclic dependencies
//between Engine and Environment.

namespace game {
    class Entity;
    
    class Environment : public Loggable {
        std::string description;
        std::map<std::string, Environment* > neighbors; //TODO: Weak pointers? Don´t we have normal pointers here?
        std::vector<std::unique_ptr<Entity> > entities;
        
    public:
        Environment(std::string desc);
        Environment(const Environment & env);
        Environment(Environment && env);
        virtual ~Environment();
        
        void setNeightbor(std::string direction, Environment * env);
        
        //Returns NULL if no neighbor is found in that direction.
        Environment * getNeighbor(const std::string & direction);
        
        std::string getDescription() const;
        std::vector<std::string> getDirections() const;
        
        //Transfers the ownership of the entity to the Environment.
        void addEntity(std::unique_ptr<Entity> entity);
        
        //Removes the entity from this envrionment and transfers the ownership to the caller.
        //After this is done Entity will not belong to any Environment.
        //TODO: So entities can be free? Aka temporarely not belong to any Environment? Sounds like thats impossible by the class description.
        std::unique_ptr<Entity> removeEntity(Entity * entity);
        
        std::vector<const Entity*> getEntities(bool includePlayer = false) const;
        std::vector<Entity*> getEntities(bool includePlayer = false);
        
        virtual void updateEntities();
        virtual void update();
        
        virtual std::string toString() const;
    };
}

#endif
