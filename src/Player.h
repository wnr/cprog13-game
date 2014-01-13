#ifndef __cprog13_game__Player__
#define __cprog13_game__Player__

#include "Character.h"

#include <map>
#include <vector>

namespace game {
    class Player : public Character {
        std::map<std::string, std::function<bool(const std::vector<std::string> &)>> commands;
        
    public:
        Player(Engine * engine, int maxHealth, std::string name);
        Player(const Player & player);
        Player(Player && player);
        virtual ~Player();
        
        void update(const Environment & env);
        
        std::string toString() const;
        
    private:
        void initCommands();
        bool performCommand(const std::vector<std::string> & inputs);
    };
}

#endif
