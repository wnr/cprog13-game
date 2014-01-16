#include "Engine.h"

#include "Environment.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"
#include "Chest.h"
#include "Key.h"
#include "Backpack.h"

#include "Constants.h"
#include "Log.h"

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

Engine & Engine::getInstance() {
    static Engine instance;
    return instance;
}

void Engine::initEnvironments() {
    std::unique_ptr<Environment> home(new Environment("Home", "a big house with walls."));
    std::unique_ptr<Environment> outside(new Environment("Outside home", "an outside place with big sun."));
    std::unique_ptr<Environment> street54(new Environment("Street 54","an street just outside your home."));
    std::unique_ptr<Environment> statoil(new Environment("Statoil","your favorite gas station."));
    std::unique_ptr<Environment> flanders(new Environment("Flanders","awful neighbours."));
    std::unique_ptr<Environment> mcDonalds(new Environment("MC","mmm burgers."));
    std::unique_ptr<Environment> church(new Environment("Church","god is watching."));
    
    home->setNeightbor("outside", outside.get());
    home->addObject(std::unique_ptr<PhysicalObject>(new Player(1337, "Lucas")));
    home->addObject(std::unique_ptr<PhysicalObject>(new Monster("Troll", 100)));
    home->addObject(std::unique_ptr<PhysicalObject>(new Weapon(2)));
    std::unique_ptr<Key>  key(new Key(3, "Standard_key"));
    home->addObject(std::unique_ptr<PhysicalObject>(new Chest(10, key.get())));
    
    //TODO: Strange crash when player is added before other objects!
    
    outside->setNeightbor("inside", home.get());
    outside->setNeightbor("street", street54.get());
    outside->addObject(std::unique_ptr<PhysicalObject>(new Monster("Troll", 100)));
    outside->addObject(std::move(key));
    street54->setNeightbor("outside_home", outside.get());
    street54->setNeightbor("statoil", statoil.get());
    street54->setNeightbor("flanders", flanders.get());
    street54->setNeightbor("mcDonalds", mcDonalds.get());
    street54->setNeightbor("church", church.get());
    statoil->setNeightbor("street", street54.get());
    flanders->setNeightbor("street", street54.get());
    mcDonalds->setNeightbor("street", street54.get());
    mcDonalds->addObject(std::unique_ptr<PhysicalObject>(new Chest(10)));
    church->setNeightbor("street", street54.get());

    push_back(std::move(home));
    push_back(std::move(outside));
    push_back(std::move(street54));
    push_back(std::move(statoil));
    push_back(std::move(flanders));
    push_back(std::move(mcDonalds));
    push_back(std::move(church));
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
        
        std::cout << std::endl;
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