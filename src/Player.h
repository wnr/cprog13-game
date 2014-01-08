#ifndef __cprog13_game__Player__
#define __cprog13_game__Player__

#include "Entity.h"

#define ENTITY_PLAYER_TYPE "Player"

namespace game {
    class Player : public Entity {
        std::string name;
        
    public:
        Player(Engine * engine, std::string name);
        Player(const Player & player);
        Player(Player && player);
        
        void update();
    };
}

#endif
