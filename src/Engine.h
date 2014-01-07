#ifndef __cprog13_game__Engine__
#define __cprog13_game__Engine__

#include <string>
#include <vector>

#define INPUT_WORD_DELIMETER    " "
#define INPUT_INDICATOR         "> "

namespace game {
    class Engine {
    public:
        Engine();
        ~Engine();
        
        void run();
        
    private:
        std::vector<std::string> getInput();
    };
}

#endif