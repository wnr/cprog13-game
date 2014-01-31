CC = g++
CCFLAGS = -g -std=c++0x

SRC_PATH = src

FILES = Armor.cpp	Character.cpp Container.cpp Environment.cpp Ghost.cpp	Item.cpp LockableContainer.cpp PhysicalObject.cpp rand.cpp Troll.cpp BaseObject.cpp	Chest.cpp	Demon.cpp Equipment.cpp Graveyard.cpp Key.cpp main.cpp Player.cpp	Shield.cpp Vampire.cpp BreakableItem.cpp Consumable.cpp Engine.cpp Food.cpp Inventory.cpp KeyLock.cpp Monster.cpp	Potion.cpp SpawnArea.cpp Weapon.cpp

SOURCES = $(FILES:%.cpp=$(SRC_PATH)/%.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

all: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o game
	
clean:
	rm -f $(OBJECTS)
	rm -f game
