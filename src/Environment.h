#ifndef __cprog13_game__Environment__
#define __cprog13_game__Environment__

#include <iostream>
#include <string>
#include <map>
#include <vector>

namespace game {
    class Entity;
    
    class Environment {
        std::string description;
        std::map<std::string, std::weak_ptr<Environment> > neighbors;
        std::vector<std::weak_ptr<Entity> > entities;
        
    public:
        Environment(std::string desc);
        Environment(const Environment & env);
        Environment(Environment && env);
        ~Environment();
        
        void setNeightbor(std::string direction, std::weak_ptr<Environment> env);
        std::weak_ptr<Environment> getNeighbor(const std::string & direction);
        
        std::string getDescription() const;
        std::vector<std::string> getDirections() const;
        
        void addEntity(std::weak_ptr<Entity> entity);
        void removeEntity(std::weak_ptr<Entity> entity);
        std::weak_ptr<Entity> removeEntity(const Entity * entity);
        
        virtual void updateEntities();
        virtual void update();
    };
}

#endif
