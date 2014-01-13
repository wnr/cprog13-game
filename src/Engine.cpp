#include "Engine.h"

#include "Environment.h"
#include "Player.h"
#include "Monster.h"

#include "Constants.h"
#include "Log.h"

#include <iostream>
#include <cstring>

using namespace game;
using std::vector;
using std::string;

Engine::Engine() {
    running = true;
    
    initEnvironments();
}

Engine::~Engine() {}

void Engine::initEnvironments() {
    std::unique_ptr<Environment> house(new Environment("a big house with walls."));
    std::unique_ptr<Environment> outside(new Environment("an outside place with big sun"));
    
    house->setNeightbor("outside", outside.get());
    house->addEntity(std::unique_ptr<Entity>(new Player(this, 1337, "Lucas")));
    outside->setNeightbor("inside", house.get());
    outside->addEntity(std::unique_ptr<Entity>(new Monster(this, "Troll", 100)));
    
    environments.push_back(std::move(house));
    environments.push_back(std::move(outside));
}

void Engine::run() {
    printIntro();
    
    while(running) {
        
        for(auto env = environments.begin(); env != environments.end(); env++) {
            (*env)->update();
        }
        
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