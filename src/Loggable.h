#ifndef __cprog13_game__Loggable__
#define __cprog13_game__Loggable__

namespace game {
    class Loggable {
    public:
        virtual std::string toString() const = 0;
    };
}

#endif
