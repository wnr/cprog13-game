#include "Engine.h"

#include <iostream>
#include <cstring>

using namespace game;
using std::vector;
using std::string;

Engine::Engine() {
    
}

Engine::~Engine() {
    
}

void Engine::run() {
    vector<string> input;
    
    printIntro();
    
    while(true) {
        std::cout << INPUT_INDICATOR;
        
        input = getInput();
        
        for_each(input.begin(), input.end(), [] (string word) {
            std::cout << word << "-";
        });
        
        std::cout << std::endl;
    }
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

void Engine::printIntro() {
    std::cout << GAME_INTRO << std::endl;
}