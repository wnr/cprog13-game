#ifndef __cprog13_game__Utils__
#define __cprog13_game__Utils__

//Helper methods for dealing with any general problems regarding the game

#include <string>

namespace game {
    std::string unsignedValToString(int val) {
        if(val == -1) {
            return "UNKNOWN";
        }
        
        return std::to_string(val);
    }
}

#endif
