#include "Key.h"

using namespace game;

Key::Key(const Key & key) : Item(key), level(key.level), identifier(key.identifier) {}

Key::Key(Key && key) : Item(key), level(key.level), identifier(key.identifier) {}

Key::~Key() {}

bool Key::operator==(const Key & key) const{
    if(key.identifier == identifier) {
        return true;
    }
    return false;
}

bool Key::operator>=(const Key & key) const{
    return differenceOperator(key, [](int self, int other){ return self >= other; });
}

bool Key::operator>(const Key & key) const{
    return differenceOperator(key, [](int self, int other){ return self > other; });
}

bool Key::operator<=(const Key & key) const{
    return differenceOperator(key, [](int self, int other){ return self <= other; });
}

bool Key::operator<(const Key & key) const{
    return differenceOperator(key, [](int self, int other){ return self < other; });
}

bool Key::differenceOperator(const Key & key, const std::function<int(int, int)> & operation) const {
    return operation(level, key.level);
}

std::string Key::toString() const {
    return type;
}