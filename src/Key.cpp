#include "Key.h"
#include "Constants.h"

using namespace game;

Key::Key() : Key(KEY_STANDARD_LEVEL) {}

Key::Key(int level) : Key(level, KEY_STANDARD_IDENTIFIER, ITEM_TYPE_KEY) {}

Key::Key(std::string identfier) : Key(KEY_STANDARD_LEVEL, identifier, ITEM_TYPE_KEY) {}

Key::Key(int level, std::string identifier, std::string name) : Item(ITEM_TYPE_KEY, 0, name), level(level), identifier(identifier){}

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

int Key::getLevel() const {
    return level;
}

std::string Key::getIdentifier() const {
    return identifier;
}

std::string Key::getPersonalDescription() const {
    return "A " + getName() + ". You know... to unlock stuff.";
}