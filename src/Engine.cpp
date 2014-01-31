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
#include "DemonBoss.h"

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
    
    auto createSpawnEnv = [this](std::string name, std::string desc, std::vector<PhysicalObject *> physicalObjects, std::vector<int> spawnChances) -> Environment * {
        
        if(spawnChances.size() != physicalObjects.size()) {
            throw new std::invalid_argument("Spawnchans vector and pbject vector must be same size!");
        }
        std::vector<std::shared_ptr<SpawnEntry>> vector;
        
        for(int i = 0; i < physicalObjects.size(); i++) {
            auto object = std::shared_ptr<PhysicalObject>(physicalObjects[i]);
            auto spawnEntry = std::shared_ptr<SpawnEntry>(new SpawnEntry(object, spawnChances[i]));
            vector.push_back(spawnEntry);
        }

        SpawnArea * env = new SpawnArea(name, desc, vector);
        
        this->push_back(std::unique_ptr<Environment>(env));
        return env;
    };
    
    auto connectEnvs = [](Environment * env1, Environment * env2, std::string desc1, std::string desc2) {
        env1->setNeightbor(desc1, env2);
        env2->setNeightbor(desc2, env1);
    };
    
    
    auto getEmptyRat = []() {
        return new Monster(NULL, CHARACTER_TYPE_RAT, RAT_HEALTH, CHARACTER_TYPE_RAT, RAT_MOVE_PROB, RAT_ATTACK_PROB, RAT_BASE_ARMOR, RAT_BASE_DODGE, RAT_BASE_BLOCK, RAT_BASE_MIN_DMG, RAT_BASE_MAX_DMG, RAT_BASE_CRIT_PROB, RAT_BASE_CRIT_MOD);
    };
    
    auto getEmptyOgre = []() {
        return new Troll(NULL, CHARACTER_TYPE_TROLL, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
    };
    
    //places
    Environment * home = createEnv(new Environment(ENV_HOME_NAME, ENV_HOME_DESC));
    Environment * neighHall = createEnv(new Environment(ENV_NEIGH_HALL_NAME, ENV_NEIGH_HALL_DESC));
    Environment * neighKitchen = createEnv(new Environment(ENV_NEIGH_KITCHEN_NAME, ENV_NEIGH_KITCHEN_DESC));
    Environment * neighGarden = createEnv(new Environment(ENV_NEIGH_BACKSIDE_NAME, ENV_NEIGH_BACKSIDE_DESC));
    Environment * market = createSpawnEnv(ENV_MARKET_NAME, ENV_MARKET_DESC, {getEmptyRat()}, {5});
    Environment * marketStorage = createSpawnEnv(ENV_MARKET_STORAGE_NAME, ENV_MARKET_STORAGE_DESC, {
        new Food("Cheese", 200),
        new Food("Meat", 400),
        new Food("Pizza", 300),
        new Food("Suger", 100),
        new Food("Hamburger", 500),
        getEmptyRat()}, {
            4,
            4,
            2,
            5,
            1,
            5,});
    Environment * graveyard = createEnv(new Environment(ENV_GRAVEYARD_NAME, ENV_GRAVEYARD_DESC));
    Environment * forestEntrance = createEnv(new Environment(ENV_FOREST_ENTRANCE_NAME, ENV_FOREST_ENTRANCE_DESC));
    Environment * forestWest = createSpawnEnv(ENV_FOREST_WEST_NAME, ENV_FOREST_WEST_DESC, {new Troll(NULL)}, {1});
    Environment * forestNorth = createSpawnEnv(ENV_FOREST_NORTH_NAME, ENV_FOREST_NORTH_DESC, {new Troll(NULL)}, {1});
    Environment * forestNorthEast = createSpawnEnv(ENV_FOREST_NORTH_EAST_NAME, ENV_FOREST_NORTH_EAST_DESC, {new Troll(NULL), getEmptyOgre()}, {1, 1});
    Environment * forestEast = createSpawnEnv(ENV_FOREST_EAST_NAME, ENV_FOREST_EAST_DESC, {new Troll(NULL)}, {1});
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

    auto addRat = [](Environment * env){
        new Monster(env, CHARACTER_TYPE_RAT, RAT_HEALTH, CHARACTER_TYPE_RAT, RAT_MOVE_PROB, RAT_ATTACK_PROB, RAT_BASE_ARMOR, RAT_BASE_DODGE, RAT_BASE_BLOCK, RAT_BASE_MIN_DMG, RAT_BASE_MAX_DMG, RAT_BASE_CRIT_PROB, RAT_BASE_CRIT_MOD);
    };
    
    auto addOgre = [](Environment * env) {
        return new Troll(env, CHARACTER_TYPE_OGRE, OGRE_HEALTH, CHARACTER_TYPE_OGRE, OGRE_MOVE_PROB, OGRE_ATTACK_PROB, OGRE_BASE_ARMOR, OGRE_BASE_DODGE, OGRE_BASE_BLOCK, OGRE_BASE_MIN_DMG, OGRE_BASE_MAX_DMG, OGRE_BASE_CRIT_PROB, OGRE_BASE_CRIT_MOD);
    };
    
    auto addObject = [](Environment * env, PhysicalObject * physicalObject) {
        env->push_back(std::unique_ptr<PhysicalObject>(physicalObject));
    };
    
    auto addItemsContainer = [](Container * con, std::vector<Item *> itemList) {
        for(Item * item : itemList) {
            con->push_back(std::unique_ptr<Item>(item));
        }
    };
    
    auto addConWithItems = [](Environment * env, Container * con, std::vector<Item *> itemList) {
        for(Item * item : itemList) {
            con->push_back(std::unique_ptr<Item>(item));
        }
        env->push_back(std::unique_ptr<PhysicalObject>(con));
    };
    
    //Characters.
    new Player(home, PLAYER_HEALTH, PLAYER_NAME);
    addObject(home, new Food("Cookie", 150));

    //Monsters and items
    addRat(homeNeighPath);
    addRat(neighHall);
    addObject(neighHall, new Weapon("Katana", 50, 75, 3));
    addRat(neighKitchen);
    addConWithItems(neighKitchen, new Chest("Drawer"), {new Armor(ARMOR_TYPE_GLOVES, 5, 0, 1, "Mittens"), new Shield(25, 5, 5, 4, "Cooking_lid")});
    
    addRat(market);
    addRat(market);
    addObject(market, new Food("Cheese", 10));
    addObject(market, new Food("Meat", 15));
    addRat(marketStorage);
    addRat(marketStorage);
    addRat(marketStorage);
    addRat(marketStorage);
    addRat(marketStorage);
    addRat(marketStorage);
    addObject(marketStorage, new Potion("Pig_blood", 700));
    addObject(marketStorage, new Armor(ARMOR_TYPE_CHEST, 80, 0, 4, "Leather_chest"));
    

    addRat(forestEntrance);
    addRat(forestEntrance);
    addRat(forestEntrance);
    addRat(forestEntrance);
    addRat(forestEntrance);
    
    addRat(bishHouse);
    addRat(bishHouse);
    addRat(bishHouse);
    addRat(bishHouse);
    
    addRat(away3Path);
    addRat(away3Path);
    addRat(away3Path);
    addObject(away3Path, new Shield(40, 40, 0, 4, "Shield"));
    addObject(away3Path, new Armor(ARMOR_TYPE_SHOE, 30, 20, 4, "Shoes"));
    addObject(awayForestPath, new Weapon("Spike_club", 150, 300, 4, 10, 100));
    addObject(forestPath, new Armor(ARMOR_TYPE_PANTS, 70, 0, 4, "Pants"));
    
    
    new Troll(forestEntrance);
    addOgre(forestNorthEast);
    new Troll(forestNorthEast);
    Troll * chiefOgre = new Troll(forestNorthEast, CHARACTER_TYPE_OGRE, CHIEF_OGRE_HEALTH, CHARACTER_CHIEF_OGRE_NAME, CHIEF_OGRE_MOVE_PROB, CHIEF_OGRE_ATTACK_PROB, CHIEF_OGRE_BASE_ARMOR, CHIEF_OGRE_BASE_DODGE, CHIEF_OGRE_BASE_BLOCK, CHIEF_OGRE_BASE_MIN_DMG, CHIEF_OGRE_BASE_MAX_DMG, CHIEF_OGRE_BASE_CRIT_PROB, CHIEF_OGRE_BASE_CRIT_MOD);
    Key * armorKey = new Key(1, "ghost_chest", "Ghostly_key");
    addItemsContainer(chiefOgre->getInventory(), {armorKey});
    
    
    Chest * graveyardChest = new Chest(CHEST_SIZE, armorKey);
    addItemsContainer(graveyardChest, {
        new Weapon("Dragon_blade", 1000, 2000, 4, 15, 200),
        new Shield(75, 50, 0, 4, "Dragon_shield"),
        new Armor(ARMOR_TYPE_CHEST, 500, 0, 4, "Dragon_chest"),
        new Armor(ARMOR_TYPE_HELMET, 300, 5, 4, "Dragon_helmet"),
        new Armor(ARMOR_TYPE_PANTS, 250, 0, 4, "Dragon_pants"),
        new Armor(ARMOR_TYPE_GLOVES, 150, 5, 4, "Dragon_gloves"),
        new Armor(ARMOR_TYPE_SHOE, 200, 10, 4, "Dragon_shoes")
    });
    
    addObject(graveyard, graveyardChest);
    new Vampire(graveyard);
    new Ghost(graveyard);
    
    new Demon(bishHouse);
    
    new Demon(bishSecret);
    new Demon(bishSecret);
    Chest * secretChest = new Chest();
    addItemsContainer(secretChest, {new Potion("Bear_piss", 600), new Food("Protein_shake", 1000), new Food("Protein_shake", 1000), new Food("Protein_shake", 1000)});
    addObject(bishSecret, secretChest);
    
    new Demon(cathHall);
    
    new DemonBoss(cathBoss);
    new Demon(cathBoss);
    new Demon(cathBoss);
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
