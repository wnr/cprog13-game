#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>
#include <map>

#include "Environment.h"

#define INPUT_WORD_DELIMETER    " "
#define INPUT_INDICATOR         "> "
#define INPUT_INVALID_COMMAND   "Invalid command.";

#define GAME_INTRO              "This is a magic game with magic and stuff. Type 'exit' to exit, otherwise just follow the instructions."
#define GAME_OUTRO              "Good bye sissy."

namespace game {
    class Engine {
        bool running;
        std::map<std::string, std::function<bool(Engine*, const std::vector<std::string> &)>> commands;
        std::vector<std::shared_ptr<Environment> > environments;
        std::weak_ptr<Environment> currentEnv;
    public:
        Engine();
        ~Engine();
        
        void run();
        
        void setCurrentEnvironment(std::weak_ptr<Environment> env);
        std::weak_ptr<Environment> getCurrentEnvironment();
        
    private:
        std::vector<std::string> getInput() const;
        bool performCommand(const std::vector<std::string> & inputs);
        void printIntro() const;
        void printOutro() const;
        
        void initCommands();
        void initEnvironments();
    };
}

#endif