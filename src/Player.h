#ifndef __cprog13_game__Player__
#define __cprog13_game__Player__

#include "Entity.h"

namespace game {
    class Player : public Entity {
        std::string name;
        
    public:
        Player(Engine * engine, std::string name);
        Player(const Player & player);
        Player(Player && player);
        
        void update(const Environment & env);
    };
}

#endif
