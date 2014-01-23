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
    
    inline float incByPercent(float percent, unsigned int incPercent) {
        if(percent < 0.0 || percent > 1.0 || incPercent > 100) {
            throw std::invalid_argument("Bad percentage: " + std::to_string(percent) + " or incPercent: " + std::to_string(incPercent));
        }
        float inversePercent = 1.0 - percent;
        float inverseIncPercent = 1.0 - incPercent / 100.0;
        float newPercent = 1.0 - inversePercent * inverseIncPercent;
        return newPercent;
    }
    
    inline unsigned int convertPercent(float percent) {
        return ((percent*100.0) + 0.5);
    }
}

#endif
