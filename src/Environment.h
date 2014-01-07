#ifndef __cprog13_game__Environment__
#define __cprog13_game__Environment__

#include <iostream>
#include <string>
#include <map>

namespace game {
    class Environment {
        std::string description;
        std::map<std::string, std::weak_ptr<Environment> > neighbors;
        
    public:
        Environment(std::string desc);
        Environment(const Environment & env);
        Environment(Environment && env);
        ~Environment();
        
        void setNeightbor(std::string direction, std::weak_ptr<Environment> env);
        std::weak_ptr<Environment> getNeighbor(const std::string & direction);
        
        std::string getDescription() const;
    };
}

#endif
