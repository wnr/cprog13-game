#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>
#include <map>

#include "Object.h"

//Engine of the game. Holds and owns all environments. Everything Engine owns is freed when Engine is destructed.
//All environments are guaranteed during lifetime of Engine.

int main(int argc, const char * argv[]);

namespace game {
    class Environment;
    
    class Engine {
        bool running;
        std::vector<std::unique_ptr<Environment> > environments;
    public:
        friend int ::main(int argc, const char * argv[]);
        friend Engine & Object::getEngine() const;
        
        ~Engine();
        
        void run();
        void kill();
        
        std::vector<std::string> getInput() const;
        
    private:
        
        static Engine & getInstance() {
            static Engine instance; // Guaranteed to be destroyed and instantiated on first use.
            return instance;
        }
        
        Engine();
        
        void printIntro() const;
        void printOutro() const;
        
        void initEnvironments();
    };
}

#endif