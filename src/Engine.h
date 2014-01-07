#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>

#define INPUT_WORD_DELIMETER    " "
#define INPUT_INDICATOR         "> "

#define GAME_INTRO              "This is a magic game with magic and stuff. Type 'exit' to exit, otherwise just follow the instructions."

namespace game {
    class Engine {
    public:
        Engine();
        ~Engine();
        
        void run();
        
    private:
        std::vector<std::string> getInput();
        void printIntro();
    };
}

#endif