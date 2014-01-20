#include "Utils.h"

using namespace game;

std::string Utils::unsignedValToString(int val) {
    if(val == -1) {
        return "UNKNOWN";
    } else {
        return std::to_string(val);
    }
}