#include "Engine.h"

#include <iostream>
#include <cstring>

using namespace game;
using std::vector;
using std::string;

Engine::Engine() {
    running = true;
    
    commands["exit"] = [](Engine *engine){
        engine->running = false;
    };
}

Engine::~Engine() {
    
}

void Engine::run() {
    printIntro();
    
    while(running) {
        std::cout << INPUT_INDICATOR;
        
        if(!performCommand(getInput())) {
            std::cout << INPUT_INVALID_COMMAND;
            std::cout << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    printOutro();
}

vector<string> Engine::getInput() {
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
    
    std::function<void(Engine*)> command = commands[key];
    command(this);
    
    return true;
}

void Engine::printIntro() {
    std::cout << GAME_INTRO << std::endl;
}

void Engine::printOutro() {
    std::cout << GAME_OUTRO << std::endl;
}