#ifndef __cprog13_game__Player__
#define __cprog13_game__Player__

#include "Character.h"

#include <map>
#include <vector>

namespace game {
    class Player : public Character {
        std::map<std::string, std::function<bool(Environment & env, const std::vector<std::string> &)>> commands;
        
    public:
        Player(unsigned int maxHealth, std::string name);
        Player(const Player & player);
        Player(Player && player);
        ~Player();
        
        void update(Environment & env);
        
        void interact(Character * other);
        
    private:
        void initCommands();
        bool performCommand(Environment & env, const std::vector<std::string> & inputs);
    };
}

#endif
