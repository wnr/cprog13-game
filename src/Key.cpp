#include "Key.h"

using namespace game;

Key::Key() : Key(KEY_STANDARD_LEVEL) {}

Key::Key(int level) : Key(level, KEY_STANDARD_IDENTIFIER) {}

Key::Key(std::string identfier) : Key(KEY_STANDARD_LEVEL, identifier) {}

Key::Key(int level, std::string identifier) : Item(ITEM_KEY_TYPE,true), level(level), identifier(identifier){}

Key::Key(const Key & key) : Item(key), level(key.level), identifier(key.identifier) {}

Key::Key(Key && key) : Item(key), level(key.level), identifier(key.identifier) {}

Key::~Key() {}

bool Key::operator==(const Key & key) const {
    return key.identifier == identifier;
}

bool Key::operator>=(const Key & key) const {
    return differenceOperator(key, [](int self, int other){ return self >= other; });
}

bool Key::operator>(const Key & key) const {
    return differenceOperator(key, [](int self, int other){ return self > other; });
}

bool Key::operator<=(const Key & key) const {
    return differenceOperator(key, [](int self, int other){ return self <= other; });
}

bool Key::operator<(const Key & key) const {
    return differenceOperator(key, [](int self, int other){ return self < other; });
}

bool Key::differenceOperator(const Key & key, const std::function<bool(int, int)> & operation) const {
    return operation(level, key.level);
}