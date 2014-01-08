#include "Engine.h"

#include "Environment.h"
#include "Player.h"

#include "Constants.h"

#include <iostream>
#include <cstring>

using namespace game;
using std::vector;
using std::string;

Engine::Engine() {
    running = true;
    player = std::shared_ptr<Player>(new Player(this, "Lucas"));
    
    initCommands();
    initEnvironments();
}

Engine::~Engine() {
    
}

void Engine::initCommands() {
    commands["exit"] = [](Engine *engine, const std::vector<std::string> &) -> bool {
        engine->running = false;
        return true;
    };
    
    commands["go"] = [](Engine * engine, const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            return false;
        }
        
        return engine->player->move(commands[1]);
    };
}

void Engine::initEnvironments() {
    std::shared_ptr<Environment> house(new Environment("a big house with walls."));
    std::shared_ptr<Environment> outside(new Environment("an outside place with big sun"));
    
    house->setNeightbor("forward", outside);
    house->addEntity(std::static_pointer_cast<Entity>(player));
    outside->setNeightbor("backward", house);
    
    environments.push_back(house);
    environments.push_back(outside);
}

void Engine::run() {
    printIntro();
    
    while(running) {
        
        for(auto env : environments) {
            env->update();
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

bool Engine::performCommand(const vector<string> & input) {
    if(input.empty()) {
        return false;
    }
    
    string key = input[0];
    
    if(commands.count(key) == 0) {
        return false;
    }
    
    auto command = commands[key];
    return command(this, input);
}

void Engine::printIntro() const {
    std::cout << GAME_INTRO << std::endl;
}

void Engine::printOutro() const {
    std::cout << GAME_OUTRO << std::endl;
}