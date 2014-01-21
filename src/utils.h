#ifndef __cprog13_game__utils__
#define __cprog13_game__utils__

//Helper methods for dealing with any general problems regarding the game

#include <string>
#include "Constants.h"

namespace game {
    inline std::string unsignedValToString(int val) {
        if(val == -1) {
            return INFORMATION_UNKNOWN;
        }
        
        return std::to_string(val);
    }
    
    inline std::string toLowerCase(std::string word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        return word;
    }
}

#endif
