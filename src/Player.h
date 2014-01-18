#ifndef __cprog13_game__Player__
#define __cprog13_game__Player__

#include "Character.h"

#include <map>
#include <vector>

namespace game {
    class Player : public Character {
        std::map<std::string, std::function<bool(const std::vector<std::string> &)>> commands;
        
    public:
        Player(Environment * env, unsigned int maxHealth, std::string name);
        Player(const Player & player);
        Player(Player && player);
        ~Player();
        
        void update(Environment & env);
        
        void interact(Character * other);
        unsigned int attack(unsigned int hp);
        
    private:
        void update();
        void initCommands();
        
        void printUpdateInfo() const;
        bool performCommand(const std::vector<std::string> & inputs);
    };
}

#endif
