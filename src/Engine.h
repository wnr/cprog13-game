#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>
#include <map>

namespace game {
    class Environment;
    class Player;
    
    class Engine {
        bool running;
        std::shared_ptr<Player> player;
        std::map<std::string, std::function<bool(Engine*, const std::vector<std::string> &)>> commands;
        std::vector<std::shared_ptr<Environment> > environments;
    public:
        Engine();
        ~Engine();
        
        void run();
        
        std::vector<std::string> getInput() const;
        bool performCommand(const std::vector<std::string> & inputs);
        
    private:
        void printIntro() const;
        void printOutro() const;
        
        void initCommands();
        void initEnvironments();
    };
}

#endif