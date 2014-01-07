#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>
#include <map>

#define INPUT_WORD_DELIMETER    " "
#define INPUT_INDICATOR         "> "
#define INPUT_INVALID_COMMAND   "Invalid command.";

#define GAME_INTRO              "This is a magic game with magic and stuff. Type 'exit' to exit, otherwise just follow the instructions."
#define GAME_OUTRO              "Good bye sissy."

namespace game {
    class Engine {
        bool running;
        std::map<std::string, std::function<void(Engine*)>> commands;
    public:
        Engine();
        ~Engine();
        
        void run();
        
    private:
        std::vector<std::string> getInput();
        bool performCommand(const std::vector<std::string> & inputs);
        void printIntro();
        void printOutro();
    };
}

#endif