#ifndef cprog13_game_Log_h
#define cprog13_game_Log_h

#include <iostream>
#include "Loggable.h"

namespace game {
    inline void log(const std::string & text) {
        std::cerr << text << std::endl;
    }
    
    inline void log(const game::Loggable * obj, const std::string & text) {
        log(obj->toString() + ": " + text);
    }
    
    inline void error(const game::Loggable * obj, const std::string & text) {
        log("-ERROR- " + obj->toString() + ": " + text);
    }
}

#endif
