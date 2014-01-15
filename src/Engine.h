#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>
#include <map>

#include "Object.h"
#include "OwningVector.h"

//Engine of the game. Holds and owns all environments. Everything Engine owns is freed when Engine is destructed.
//All environments are guaranteed during lifetime of Engine.

int main(int argc, const char * argv[]);

namespace game {
    class Environment;
    
    class Engine : private OwningVector<Environment> {
        bool running;
    public:
        //Only main function and Object can access engine.
        friend int ::main(int argc, const char * argv[]);
        friend Engine & Object::getEngine() const;
        
        ~Engine();
        
        void run();
        void kill();
        
        std::vector<std::string> getInput() const;
        
    private:
        Engine();
        
        static Engine & getInstance();
        
        void printIntro() const;
        void printOutro() const;
        
        void initEnvironments();
    };
}

#endif