#include "Engine.h"

#include "Environment.h"
#include "Player.h"
#include "Troll.h"
#include "Weapon.h"
#include "Chest.h"
#include "Key.h"
#include "Inventory.h"
#include "Graveyard.h"
#include "Demon.h"
#include "Food.h"
#include "Shield.h"
#include "SpawnArea.h"
#include "Potion.h"
#include "Ghost.h"
#include "Vampire.h"

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
    
    auto connectEnvs = [](Environment * env1, Environment * env2, std::string desc1, std::string desc2) {
        env1->setNeightbor(desc1, env2);
        env2->setNeightbor(desc2, env1);
    };
    
    
    //places
    Environment * home = createEnv(new Environment(ENV_HOME_NAME, ENV_HOME_DESC));
    Environment * neighHall = createEnv(new Environment(ENV_NEIGH_HALL_NAME, ENV_NEIGH_HALL_DESC));
    Environment * neighKitchen = createEnv(new Environment(ENV_NEIGH_KITCHEN_NAME, ENV_NEIGH_KITCHEN_DESC));
    Environment * neighGarden = createEnv(new Environment(ENV_NEIGH_BACKSIDE_NAME, ENV_NEIGH_BACKSIDE_DESC));
    Environment * market = createEnv(new Environment(ENV_MARKET_NAME, ENV_MARKET_DESC));
    Environment * marketStorage = createEnv(new Environment(ENV_MARKET_STORAGE_NAME, ENV_MARKET_STORAGE_DESC));
    Environment * graveyard = createEnv(new Environment(ENV_GRAVEYARD_NAME, ENV_GRAVEYARD_DESC));
    Environment * forestEntrance = createEnv(new Environment(ENV_FOREST_ENTRANCE_NAME, ENV_FOREST_ENTRANCE_DESC));
    Environment * forestWest = createEnv(new Environment(ENV_FOREST_WEST_NAME, ENV_FOREST_WEST_DESC));
    Environment * forestNorth = createEnv(new Environment(ENV_FOREST_NORTH_NAME, ENV_FOREST_NORTH_DESC));
    Environment * forestNorthEast = createEnv(new Environment(ENV_FOREST_NORTH_EAST_NAME, ENV_FOREST_NORTH_EAST_DESC));
    Environment * forestEast = createEnv(new Environment(ENV_FOREST_EAST_NAME, ENV_FOREST_EAST_DESC));
    Environment * bishHouse = createEnv(new Environment(ENV_BISH_HOUSE_NAME, ENV_BISH_HOUSE_DESC));
    Environment * bishSecret = createEnv(new Environment(ENV_BISH_HOUSE_SECRET_ROOM_NAME, ENV_BISH_HOUSE_SECRET_ROOM_DESC));
    Environment * cathHall = createEnv(new Environment(ENV_CATH_HALL_NAME, ENV_CATH_HALL_DESC));
    Environment * cathWest = createEnv(new Environment(ENV_CATH_WING_WEST_NAME, ENV_CATH_WING_WEST_DESC));
    Environment * cathEast = createEnv(new Environment(ENV_CATH_WING_EAST_NAME, ENV_CATH_WING_EAST_DESC));
    Environment * cathBoss = createEnv(new Environment(ENV_CATH_BOSS_ROOM_NAME, ENV_CATH_BOSS_ROOM_DESC));
    
    //Streets
    Environment * homePath = createEnv(new Environment(ENV_HOME_PATH_NAME, ENV_HOME_PATH_DESC));
    Environment * homeNeighPath = createEnv(new Environment(ENV_NEIGH_HOME_PATH_NAME, ENV_NEIGH_HOME_PATH_DESC));
    Environment * neighMarketPath = createEnv(new Environment(ENV_NEIGH_MARKET_PATH_NAME, ENV_NEIGH_MARKET_PATH_DESC));
    Environment * marketAwayPath = createEnv(new Environment(ENV_MARKET_AWAY_PATH_NAME, ENV_MARKET_AWAY_PATH_DESC));
    Environment * marketStoragePath = createEnv(new Environment(ENV_MARKET_STORAGE_PATH_NAME, ENV_MARKET_STORAGE_PATH_DESC));
    Environment * homeAwayPath = createEnv(new Environment(ENV_HOME_AWAY_PATH_NAME, ENV_HOME_AWAY_PATH_DESC));
    Environment * away1Path = createEnv(new Environment(ENV_AWAY_PATH_1_NAME, ENV_AWAY_PATH_1_DESC));
    Environment * away2Path = createEnv(new Environment(ENV_AWAY_PATH_2_NAME, ENV_AWAY_PATH_2_DESC));
    Environment * away3Path = createEnv(new Environment(ENV_AWAY_PATH_3_NAME, ENV_AWAY_PATH_3_DESC));
    Environment * awayCathPath = createEnv(new Environment(ENV_AWAY_CATH_PATH_NAME, ENV_AWAY_CATH_PATH_DESC));
    Environment * cathBishPath = createEnv(new Environment(ENV_CATH_BISH_PATH_NAME, ENV_CATH_BISH_PATH_DESC));
    Environment * cathPath = createEnv(new Environment(ENV_CATH_PATH_NAME, ENV_CATH_PATH_DESC));
    Environment * awayForestPath = createEnv(new Environment(ENV_AWAY_FOREST_PATH_NAME, ENV_AWAY_FOREST_PATH_DESC));
    Environment * graveyardPath = createEnv(new Environment(ENV_GRAVEYARD_PATH_NAME, ENV_GRAVEYARD_PATH_DESC));
    Environment * forestPath = createEnv(new Environment(ENV_FOREST_PATH_NAME, ENV_FOREST_PATH_DESC));
    
    //Connections
    connectEnvs(home, homePath, ENVCON_HOME_WITH_HOME_PATH, ENVCON_HOME_PATH_WITH_HOME);
    connectEnvs(homePath, homeAwayPath, ENVCON_HOME_PATH_WITH_HOME_AWAY_PATH, ENVCON_HOME_AWAY_PATH_WITH_HOME_PATH);
    connectEnvs(homePath, homeNeighPath, ENVCON_HOME_PATH_WITH_NEIGH_HOME_PATH, ENVCON_NEIGH_HOME_PATH_WITH_HOME_PATH);
    connectEnvs(homeNeighPath, neighHall, "", "");
    connectEnvs(homeNeighPath, neighMarketPath, ENVCON_NEIGH_HOME_PATH_WITH_NEIGH_MARKET_PATH, ENVCON_NEIGH_MARKET_PATH_WITH_NEIGH_HOME_PATH);
    connectEnvs(neighHall, neighMarketPath, ENVCON_NEIGH_HALL_WITH_NEIGH_MARKET_PATH, ENVCON_NEIGH_MARKET_PATH_WITH_NEIGH_HALL);
    connectEnvs(neighHall, neighKitchen, ENVCON_NEIGH_HALL_WITH_NEIGH_KITCHEN, ENVCON_NEIGH_KITCHEN_WITH_NEIGH_HALL);
    connectEnvs(neighKitchen, neighGarden, ENVCON_NEIGH_KITCHEN_WITH_NEIGH_GARDEN, ENVCON_NEIGH_GARDEN_WITH_NEIGH_KITCHEN);
    connectEnvs(neighMarketPath, market, ENVCON_NEIGH_MARKET_PATH_WITH_MARKET, ENVCON_MARKET_WITH_NEIGH_MARKET_PATH);
    connectEnvs(market, marketStoragePath, ENVCON_MARKET_WITH_MARKET_STORAGE_PATH, ENVCON_STORAGE_PATH_WITH_MARKET);
    connectEnvs(marketStoragePath, marketStorage, ENVCON_STORAGE_PATH_WITH_STORAGE, ENVCON_STORAGE_WITH_STORAGE_PATH);
    connectEnvs(neighMarketPath, marketAwayPath, ENVCON_NEIGH_MARKET_PATH_WITH_MARKET_AWAY_PATH, ENVCON_MARKET_AWAY_PATH_WITH_NEIGH_MARKET_PATH);
    connectEnvs(market, marketAwayPath, ENVCON_MARKET_WITH_MARKET_AWAY_PATH, ENVCON_MARKET_AWAY_PATH_WITH_MARKET);
    connectEnvs(marketAwayPath, away1Path, ENVCON_MARKET_AWAY_PATH_WITH_AWAY_PATH_1, ENVCON_AWAY_PATH_1_WITH_MARKET_PATH);
    connectEnvs(marketAwayPath, homeAwayPath, ENVCON_MARKET_AWAY_PATH_WITH_HOME_AWAY_PATH, ENVCON_HOME_AWAY_PATH_WITH_MARKET_AWAY_PATH);
    connectEnvs(homeAwayPath, away1Path, ENVCON_HOME_AWAY_PATH_WITH_AWAY_PATH_1, ENVCON_AWAY_PATH_1_WITH_HOME_AWAY_PATH);
    connectEnvs(away1Path, away2Path, ENVCON_AWAY_PATH_1_WITH_AWAY_PATH_2, ENVCON_AWAY_PATH_2_WITH_AWAY_PATH_1);
    connectEnvs(away2Path, away3Path, ENVCON_AWAY_PATH_2_WITH_AWAY_PATH_3, ENVCON_AWAY_PATH_3_WITH_AWAY_PATH_2);
    connectEnvs(away3Path, awayForestPath, ENVCON_AWAY_PATH_3_WITH_FOREST_PATH_1, ENVCON_FOREST_PATH_1_WITH_AWAY_PATH_3);
    connectEnvs(away3Path, awayCathPath, ENVCON_AWAY_PATH_3_WITH_AWAY_CATH_PATH, ENVCON_AWAY_CATH_PATH_WITH_AWAY_PATH_3);
    connectEnvs(awayForestPath, awayCathPath, ENVCON_FOREST_PATH_1_WITH_AWAY_CATH_PATH, ENVCON_AWAY_CATH_PATH_WITH_FOREST_PATH_1);
    connectEnvs(awayForestPath, graveyardPath, ENVCON_FOREST_PATH_1_WITH_GRAVEYARD_PATH, ENVCON_GRAVEYARD_PATH_WITH_FOREST_PATH_1);
    connectEnvs(awayForestPath, forestPath, ENVCON_FOREST_PATH_1_WITH_FOREST_PATH_2, ENVCON_FOREST_PATH_2_WITH_FOREST_PATH_1);
    connectEnvs(graveyardPath, graveyard, "", "");
    connectEnvs(forestPath, forestEntrance, ENVCON_FOREST_PATH_2_WITH_FOREST_ENTRANCE, ENVCON_FOREST_ENTRANCE_WITH_FOREST_PATH_2);
    connectEnvs(forestEntrance, forestWest, ENVCON_FOREST_ENTRANCE_WITH_FOREST_WEST, ENVCON_FOREST_WEST_WITH_FOREST_ENTRANCE);
    connectEnvs(forestEntrance, forestNorth, ENVCON_FOREST_ENTRANCE_WITH_FOREST_NORTH, ENVCON_FOREST_NORTH_WITH_FOREST_ENTRANCE);
    connectEnvs(forestEntrance, forestNorthEast, ENVCON_FOREST_ENTRANCE_WITH_FOREST_NORTH_EAST, ENVCON_FOREST_NORTH_EAST_WITH_FOREST_ENTRANCE);
    connectEnvs(forestEntrance, forestEast, ENVCON_FOREST_ENTRANCE_WITH_FOREST_EAST, ENVCON_FOREST_EAST_WITH_FOREST_ENTRANCE);
    connectEnvs(forestWest, forestNorth, ENVCON_FOREST_WEST_WITH_FOREST_NORTH, ENVCON_FOREST_NORTH_WITH_FOREST_WEST);
    connectEnvs(forestNorth, forestNorthEast, ENVCON_FOREST_NORTH_WITH_FOREST_NORTH_EAST, ENVCON_FOREST_NORTH_EAST_WITH_FOREST_NORTH);
    connectEnvs(forestNorthEast, forestEast, ENVCON_FOREST_NORTH_EAST_WITH_FOREST_EAST, ENVCON_FOREST_EAST_WITH_FOREST_NORTH_EAST);
    connectEnvs(awayCathPath, cathBishPath, ENVCON_AWAY_CATH_PATH_WITH_CATH_BISH_PATH, ENVCON_CATH_BISH_PATH_WITH_AWAY_CATH_PATH);
    connectEnvs(cathBishPath, bishHouse, ENVCON_CATH_BISH_PATH_WITH_BISH_HOUSE, ENVCON_BISH_HOUSE_WITH_CATH_BISH_PATH);
    connectEnvs(bishHouse, bishSecret, ENVCON_BISH_HOUSE_WITH_BISH_HOUSE_SECRET, ENVCON_BISH_HOUSE_SECRET_WITH_BISH_HOUSE);
    connectEnvs(cathBishPath, cathPath, ENVCON_CATH_BISH_PATH_WITH_CATH_PATH, ENVCON_CATH_PATH_WITH_CATH_BISH_PATH);
    connectEnvs(cathPath, cathHall, ENVCON_CATH_PATH_WITH_CATH_HALL, ENVCON_CATH_HALL_WITH_CATH_PATH);
    connectEnvs(cathHall, cathWest, ENVCON_CATH_HALL_WITH_CATH_WEST_WING, ENVCON_CATH_WEST_WING_WITH_CATH_HALL);
    connectEnvs(cathHall, cathEast, ENVCON_CATH_HALL_WITH_CATH_EAST_WING, ENVCON_CATH_EAST_WING_WITH_CATH_HALL);
    connectEnvs(cathHall, cathBoss, ENVCON_CATH_HALL_WITH_CATH_BOSS_ROOM, ENVCON_CATH_BOSS_ROOM_WITH_CATH_HALL);
    
    //Characters.
    new Player(home, PLAYER_HEALTH, PLAYER_NAME);

    
    auto addRat = [](Environment * env){
        new Monster(env, CHARACTER_TYPE_RAT, RAT_HEALTH, CHARACTER_TYPE_RAT, RAT_MOVE_PROB, RAT_ATTACK_PROB, RAT_BASE_ARMOR, RAT_BASE_DODGE, RAT_BASE_BLOCK, RAT_BASE_MIN_DMG, RAT_BASE_MAX_DMG, RAT_BASE_CRIT_PROB, RAT_BASE_CRIT_MOD);
    };
    
    //Monsters.
    addRat(homeNeighPath);
    addRat(neighHall);
    addRat(neighKitchen);
    
    addRat(market);
    addRat(market);
    addRat(marketStorage);
    addRat(marketStorage);

    addRat(forestEntrance);
    addRat(forestEntrance);
    addRat(forestEntrance);
    addRat(forestEntrance);
    addRat(forestEntrance);
    
//    new Ghost(home);
//    new Ghost(home);
//    new Ghost(home);
//    new Ghost(home);
//    new Ghost(home);
//    new Ghost(home);
//    new Ghost(home);
//    new Ghost(home);
//    new Ghost(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Vampire(home);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
//    new Troll(home);
//    new Troll(home);
//    new Troll(home);
//    new Troll(home);
//    new Troll(home);
//    new Troll(home);
//    new Troll(home);
//    new Troll(home);
//    new Troll(home);


    
//    Environment * home = createEnv(new Environment("Home", "a big house with walls"));
//    Environment * outside = createEnv(new Environment("Outside home", "an outside place with big sun."));
//    Environment * street54 = createEnv(new Environment("Street 54","an street just outside your home."));
//    Environment * statoil = createEnv(new Environment("Statoil","your favorite gas station."));
//    Environment * flanders = createEnv(new Environment("Flanders","awful neighbours."));
//    Environment * mcDonalds = createEnv(new Environment("MC","mmm burgers."));
//    Environment * church = createEnv(new Environment("Church","god is watching."));
//    Environment * graveyard = createEnv(new Graveyard("Graveyard", "Ghastly place with a creepy big moon.", 10));
//    
//    home->setNeightbor("Outside", outside);
//    new Troll(home);
//    home->push_back(std::unique_ptr<PhysicalObject>(new Food("Pie")));
//    home->push_back(std::unique_ptr<PhysicalObject>(new Weapon("Axe", 10, 25, 3, 10, 50)));
//    home->push_back(std::unique_ptr<PhysicalObject>(new Shield(50, 300, 10)));
//    home->push_back(std::unique_ptr<PhysicalObject>(new Weapon(2,20)));
//    std::unique_ptr<Key>  key(new Key());
//    home->push_back(std::unique_ptr<PhysicalObject>(new Chest(10, key.get())));
//    new Player(home, 1337, "Lucas");
//    new Demon(home);
//    
//    
//    outside->setNeightbor("inside", home);
//    outside->setNeightbor("street", street54);
//    new Troll(outside);
//    outside->push_back(std::move(key));
//    street54->setNeightbor("outside_home", outside);
//    street54->setNeightbor("statoil", statoil);
//    street54->setNeightbor("flanders", flanders);
//    street54->setNeightbor("mcDonalds", mcDonalds);
//    street54->setNeightbor("church", church);
//    statoil->setNeightbor("street", street54);
//    flanders->setNeightbor("street", street54);
//    mcDonalds->setNeightbor("street", street54);
//    mcDonalds->push_back(std::unique_ptr<PhysicalObject>(new Chest(10)));
//    church->setNeightbor("street", street54);
//    church->setNeightbor("graveyard", graveyard);
//    graveyard->setNeightbor("church", church);
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