#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>
#include <map>

//Engine of the game. Holds and owns all environments. Everything Engine owns is freed when Engine is destructed.
//All environments are guaranteed during lifetime of Engine.

namespace game {
    class Environment;
    
    class Engine {
        bool running;
        std::vector<std::unique_ptr<Environment> > environments;
    public:
        Engine();
        ~Engine();
        
        void run();
        void kill();
        
        std::vector<std::string> getInput() const;
        
    private:
        void printIntro() const;
        void printOutro() const;
        
        void initEnvironments();
    };
}

#endif