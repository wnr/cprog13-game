#include "Engine.h"

#include "Environment.h"
#include "Player.h"
#include "Troll.h"
#include "Weapon.h"
#include "Chest.h"
#include "Key.h"
#include "Backpack.h"
#include "Graveyard.h"
#include "Demon.h"
#include "Food.h"

#include "Constants.h"

#include <iostream>
#include <cstring>

using namespace game;
using std::vector;
using std::string;

Engine::Engine() {
    running = false; //will be set to true when run is invoked.
    
    initEnvironments();
}

Engine::~Engine() {}

Engine * Engine::getInstance() {
    static Engine instance;
    return &instance;
}

void Engine::initEnvironments() {
    auto createEnv = [this](Environment * env) -> Environment * {
        this->push_back(std::unique_ptr<Environment>(env));
        return env;
    };
    
    Environment * home = createEnv(new Environment("Home", "a big house with walls"));
    Environment * outside = createEnv(new Environment("Outside home", "an outside place with big sun."));
    Environment * street54 = createEnv(new Environment("Street 54","an street just outside your home."));
    Environment * statoil = createEnv(new Environment("Statoil","your favorite gas station."));
    Environment * flanders = createEnv(new Environment("Flanders","awful neighbours."));
    Environment * mcDonalds = createEnv(new Environment("MC","mmm burgers."));
    Environment * church = createEnv(new Environment("Church","god is watching."));
    Environment * graveyard = createEnv(new Graveyard("Graveyard", "Ghastly place with a creepy big moon.", 10));
    
    home->setNeightbor("Outside", outside);
    new Troll(home);
    home->push_back(std::unique_ptr<PhysicalObject>(new Food("Pie")));
    home->push_back(std::unique_ptr<PhysicalObject>(new Weapon(2,2)));
    home->push_back(std::unique_ptr<PhysicalObject>(new Weapon(2,20)));
    std::unique_ptr<Key>  key(new Key());
    home->push_back(std::unique_ptr<PhysicalObject>(new Chest(10, key.get())));
    new Player(home, 1337, "Lucas");
    new Demon(home);
    
    
    outside->setNeightbor("inside", home);
    outside->setNeightbor("street", street54);
    new Troll(outside);
    outside->push_back(std::move(key));
    street54->setNeightbor("outside_home", outside);
    street54->setNeightbor("statoil", statoil);
    street54->setNeightbor("flanders", flanders);
    street54->setNeightbor("mcDonalds", mcDonalds);
    street54->setNeightbor("church", church);
    statoil->setNeightbor("street", street54);
    flanders->setNeightbor("street", street54);
    mcDonalds->setNeightbor("street", street54);
    mcDonalds->push_back(std::unique_ptr<PhysicalObject>(new Chest(10)));
    church->setNeightbor("street", street54);
    church->setNeightbor("graveyard", graveyard);
    graveyard->setNeightbor("church", church);
}

void Engine::run() {
    if(running) {
        throw std::logic_error("Engine is already running.");
    }
    
    running = true;
    
    printIntro();
    
    while(running) {
        for_each([] (Environment * env) {
            env->update();
            return true;
        });
    }
    
    printOutro();
}

vector<string> Engine::getInput() const {
    vector<string> words;
    size_t delimeterLength = sizeof(INPUT_WORD_DELIMETER)-1;
    
    string line;
    std::getline(std::cin, line);
    
    line += INPUT_WORD_DELIMETER;
    
    size_t prevPos = 0;
    size_t pos = 0;
    string word;
    while((pos = line.find(INPUT_WORD_DELIMETER, pos)) != string::npos) {
        word = line.substr(prevPos, pos - prevPos);
        if(!word.empty()) {
            words.push_back(word);
        }
        pos += delimeterLength;
        prevPos = pos;
    }
    
    return words;
}

void Engine::printIntro() const {
    std::cout << GAME_INTRO << std::endl;
}

void Engine::printOutro() const {
    std::cout << GAME_OUTRO << std::endl;
}

void Engine::kill() {
    running = false;
}