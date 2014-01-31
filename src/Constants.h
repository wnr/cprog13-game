#ifndef cprog13_game_Constants_h
#define cprog13_game_Constants_h

#define CERR_LOG                            true

#define MAXIMUM_ROTTENNESS                  5

#define OBJECT_TYPE_ENVIRONMENT             "Environment"
#define OBJECT_TYPE_GRAVEYARD_ENVIRONMENT   "Graveyard"
#define OBJECT_TYPE_CONTAINER               "Container"
#define OBJECT_TYPE_ITEM                    "Item"
#define OBJECT_TYPE_CHARACTER               "Character"
#define OBJECT_TYPE_OTHER                   "Other"

#define CHARACTER_TYPE_PLAYER               "Player"
#define CHARACTER_TYPE_MONSTER              "Monster"

#define ITEM_TYPE_WEAPON                    "Weapon"
#define ITEM_TYPE_KEY                       "Key"
#define ITEM_TYPE_CONSUMABLE                "Consumable"
#define ITEM_DURABILITY                     100

#define CONTAINER_TYPE_INVENTORY            "Inventory"
#define CONTAINER_TYPE_CHEST                "Chest"

#define ENVIRONMENT_TYPE_SPAWNER            "Spawner"

#define OTHER_TYPE_EQUIPMENT                "Equipment"

#define KEY_STANDARD_IDENTIFIER             "Standard_key"
#define KEY_STANDARD_LEVEL                  3

#define WEAPON_CRIT_PROB                    0
#define WEAPON_CRIT_MOD                     0

#define ARMOR_TYPE_HELMET                   "Helmet"
#define ARMOR_TYPE_CHEST                    "Chest"
#define ARMOR_TYPE_PANTS                    "Pants"
#define ARMOR_TYPE_SHIELD                   "Shield"
#define ARMOR_TYPE_SHOE                     "Shoe"
#define ARMOR_RATING                        5
#define ARMOR_WEIGHT                        7
#define ARMOR_DODGE_RATING                  4

#define SHIELD_BLOCK_RATING                 10
#define SHIELD_ARMOR_RATING                 15
#define SHIELD_DODGE_RATING                 2
#define SHIELD_WEIGHT                       10

#define FOOD_POTENCY                        10
#define FOOD_WEIGHT                         3
#define POTION_POTENCY                      100
#define POTEION_WEIGHT                      3

#define ATTACK_DODGED                       "dodged"
#define ATTACK_BLOCKED                      "blocked"
#define ATTACK_ABSORBED                     "absorbed"

#define OFFENCE_LIFE_STEAL                  "life stole"

#define DEFEND_REFLECT                      "reflected"


#define INVALID_CLONE                       "The element you are trying to clone does not have the function clone() implemented: "

#define LIST_ITEM_PREFIX                    "* "
#define INPUT_WORD_DELIMETER                " "
#define INPUT_INDICATOR                     "> "
#define INPUT_INVALID_COMMAND               "Invalid command. Type 'help' for command instructions."
#define INFORMATION_UNKNOWN                 "?"

#define GAME_INTRO                          "You wake up at home and you put on the local news. A demon lord named Malphas has entered the living realm and has taken the cathedral as his own! You have to do something! You also hear about the local forrest beeing invaded by trolls and ogres and that something strange is lurking in the graveyard. The apocalypse is truly upon us! Wait... could this be dream? No time to find out, time to go to battle! But you don't have any weapons. Your japanease neighbour might have a katana or something, better check there first. \n\nType 'exit' to exit, 'help' for commands and COMMAND 'help' for help with a specific command. Otherwise just follow the instructions."
#define GAME_OUTRO                          ""
#define WINNING_TEXT                        "You have vanquised the demon lord! The world can now rebuild and and push back the rest of the evil scum. The human race have you to thank and the world leaders are preparing a celebration in your hon... and you wake up."

#define TEXT_DIVIDER                        "----------"

//---- Environments ----

//Places
#define ENV_HOME_NAME                       "Inside home"
#define ENV_HOME_DESC                       "your beloved cozy house."
#define ENV_NEIGH_HALL_NAME                 "Neighbor hall"
#define ENV_NEIGH_HALL_DESC                 "the hallway of your neighbor's house."
#define ENV_NEIGH_KITCHEN_NAME              "Kitchen"
#define ENV_NEIGH_KITCHEN_DESC              "which looks a bit rusty for your taste."
#define ENV_NEIGH_BACKSIDE_NAME             "Garden"
#define ENV_NEIGH_BACKSIDE_DESC             "a beautiful garden with flowers and shit."
#define ENV_MARKET_NAME                     "Market"
#define ENV_MARKET_DESC                     "the local marketplace where you always did the groceries with your mother before she passed away."
#define ENV_MARKET_STORAGE_NAME             "Storage room"
#define ENV_MARKET_STORAGE_DESC             "the place where the sellers kept their stock back in the days when the market still was active."
#define ENV_GRAVEYARD_NAME                  "Graveyard"
#define ENV_GRAVEYARD_DESC                  "a ghastly place. Some say it's haunted. This is where your mother layes."
#define ENV_FOREST_ENTRANCE_NAME            "Forest entrance"
#define ENV_FOREST_ENTRANCE_DESC            "the entrance to the big and dusky forest."
#define ENV_FOREST_WEST_NAME                "Forest west"
#define ENV_FOREST_WEST_DESC                "the damper side of the forest. Really wet."
#define ENV_FOREST_NORTH_NAME               "Forest north"
#define ENV_FOREST_NORTH_DESC               "up on the hills."
#define ENV_FOREST_NORTH_EAST_NAME          "Forest north-east"
#define ENV_FOREST_NORTH_EAST_DESC          "the trees in this area are really scary."
#define ENV_FOREST_EAST_NAME                "Forest east"
#define ENV_FOREST_EAST_DESC                "so thick forest you can barely see anything."
#define ENV_BISH_HOUSE_NAME                 "The bishop's house"
#define ENV_BISH_HOUSE_DESC                 "the old fart used to tell you and your friends to come in for some candy when you were young..."
#define ENV_BISH_HOUSE_SECRET_ROOM_NAME     "The bishop's secret room"
#define ENV_BISH_HOUSE_SECRET_ROOM_DESC     "so the old man actually had some secrets after all!"
#define ENV_CATH_HALL_NAME                  "Cathedral entrance"
#define ENV_CATH_HALL_DESC                  "the big and grand entrance of the cathedral. It seems to be almost destroyed."
#define ENV_CATH_WING_WEST_NAME             "Right wing"
#define ENV_CATH_WING_WEST_DESC             "the room is so big you have to stand and look for a while."
#define ENV_CATH_WING_EAST_NAME             "Left wing"
#define ENV_CATH_WING_EAST_DESC             "from this view you can truly see the beauty of the cathedral."
#define ENV_CATH_BOSS_ROOM_NAME             "Cathedral altar room"
#define ENV_CATH_BOSS_ROOM_DESC             "the grandest of all rooms. You see a pesky demon eating the cross of jesus."

//Paths
#define ENV_HOME_PATH_NAME                  "Dirt path"
#define ENV_HOME_PATH_DESC                  "the path connecting your house with the bigger streets."
#define ENV_NEIGH_HOME_PATH_NAME            "Neighome street"
#define ENV_NEIGH_HOME_PATH_DESC            "the long street you used to play on when you were a child."
#define ENV_NEIGH_MARKET_PATH_NAME          "Stobor path"
#define ENV_NEIGH_MARKET_PATH_DESC          "a nice and happy walk."
#define ENV_MARKET_AWAY_PATH_NAME           "Markaway road"
#define ENV_MARKET_AWAY_PATH_DESC           "this road is a bit more dark. Not so many people used to go this way."
#define ENV_MARKET_STORAGE_PATH_NAME        "Storage path"
#define ENV_MARKET_STORAGE_PATH_DESC        "a somewhat hidden path to the market storage."
#define ENV_HOME_AWAY_PATH_NAME             "Awame path"
#define ENV_HOME_AWAY_PATH_DESC             "your mother tried to block this path for you when you were a child."
#define ENV_AWAY_PATH_1_NAME                "Dusk road 1"
#define ENV_AWAY_PATH_1_DESC                "the road your mother told you not to walk on your own back in the days."
#define ENV_AWAY_PATH_2_NAME                "Dusk road 2"
#define ENV_AWAY_PATH_2_DESC                "the road your mother would slap you in the ass for just looking at."
#define ENV_AWAY_PATH_3_NAME                "Dusk road 3"
#define ENV_AWAY_PATH_3_DESC                "the road your mother.. you get it. You shouldn't be here. Go back while you can."
#define ENV_AWAY_CATH_PATH_NAME             "Pacath street 1"
#define ENV_AWAY_CATH_PATH_DESC             "the way to what used to be the biggest cathedral of the kingdom."
#define ENV_CATH_BISH_PATH_NAME             "Pacath street 2"
#define ENV_CATH_BISH_PATH_DESC             "the smell of burnet wood and rotten flesh is filling your lungs."
#define ENV_CATH_PATH_NAME                  "Pacath street 3"
#define ENV_CATH_PATH_DESC                  "from here you can see the big cathedral. It used to be so beautiful, but now look somewhat raped."
#define ENV_AWAY_FOREST_PATH_NAME           "Frawy path 1"
#define ENV_AWAY_FOREST_PATH_DESC           "this path leads to the old forest."
#define ENV_GRAVEYARD_PATH_NAME             "Gravewalk 1"
#define ENV_GRAVEYARD_PATH_DESC             "leads to the local graveyard."
#define ENV_FOREST_PATH_NAME                "Frawy path 2"
#define ENV_FOREST_PATH_DESC                "stops directly infront of the grand forest. It looks more dusk and dark than it used to."

//---- Env Connections ----

//TODO: Do we want to keep these?
#define ENVCON_HOME_WITH_HOME_PATH                          "outside"
#define ENVCON_HOME_PATH_WITH_HOME                          "inside"
#define ENVCON_HOME_PATH_WITH_HOME_AWAY_PATH                "north-east"
#define ENVCON_HOME_AWAY_PATH_WITH_HOME_PATH                "south-west"
#define ENVCON_HOME_PATH_WITH_NEIGH_HOME_PATH               "north-west"
#define ENVCON_NEIGH_HOME_PATH_WITH_HOME_PATH               "south-east"
#define ENVCON_NEIGH_OUTSIDE_PATH_WITH_NEIGH_HALL           "inside"
#define ENVCON_NEIGH_HALL_WITH_NEIGH_OUTSIDE_PATH           "outside"
#define ENVCON_NEIGH_HOME_PATH_WITH_NEIGH_OUTSIDE_PATH      "north-west"
#define ENVCON_NEIGH_OUTSIDE_PATH_WITH_NEIGH_HOME_PATH      "south-east"
#define ENVCON_NEIGH_OUTSIDE_PATH_WITH_NEIGH_MARKET_PATH    "north-east"
#define ENVCON_NEIGH_MARKET_PATH_WITH_OUTSIDE_PATH          "south-west"
#define ENVCON_NEIGH_HALL_WITH_NEIGH_KITCHEN                "kitchen"
#define ENVCON_NEIGH_KITCHEN_WITH_NEIGH_HALL                "hall"
#define ENVCON_NEIGH_KITCHEN_WITH_NEIGH_GARDEN              "garden"
#define ENVCON_NEIGH_GARDEN_WITH_NEIGH_KITCHEN              "kitchen"
#define ENVCON_NEIGH_MARKET_PATH_WITH_MARKET                "market"
#define ENVCON_NEIGH_HALL_WITH_NEIGH_MARKET_PATH            "north-east"
#define ENVCON_NEIGH_MARKET_PATH_WITH_NEIGH_HALL            "inside"
#define ENVCON_NEIGH_HOME_PATH_WITH_NEIGH_MARKET_PATH       "north"
#define ENVCON_NEIGH_MARKET_PATH_WITH_NEIGH_HOME_PATH       "south"
#define ENVCON_NEIGH_MARKET_PATH_WITH_MARKET_OUTSIDE_PATH   "north-east"
#define ENVCON_MARKET_OUTSIDE_PATH_WITH_NEIGH_MARKET_PATH   "south-west"
#define ENVCON_MARKET_OUTSIDE_PATH_WITH_MARKET_AWAY_PATH    "south-east"
#define ENVCON_MARKET_AWAY_PATH_WITH_MARKET_OUTSIDE_PATH    "north-west"
#define ENVCON_MARKET_OUTSIDE_PATH_WITH_MARKET              "north"
#define ENVCON_MARKET_WITH_MARKET_OUTSIDE_PATH              "south"
#define ENVCON_MARKET_WITH_NEIGH_MARKET_PATH                "south-west"
#define ENVCON_MARKET_WITH_MARKET_AWAY_PATH                 "south-east"
#define ENVCON_MARKET_AWAY_PATH_WITH_MARKET                 "north-west"
#define ENVCON_MARKET_WITH_MARKET_STORAGE_PATH              "north"
#define ENVCON_STORAGE_PATH_WITH_MARKET                     "market"
#define ENVCON_STORAGE_PATH_WITH_STORAGE                    "storage"
#define ENVCON_STORAGE_WITH_STORAGE_PATH                    "west"
#define ENVCON_NEIGH_MARKET_PATH_WITH_MARKET_AWAY_PATH      "east"
#define ENVCON_MARKET_AWAY_PATH_WITH_NEIGH_MARKET_PATH      "west"
#define ENVCON_MARKET_AWAY_PATH_WITH_HOME_AWAY_PATH         "south"
#define ENVCON_HOME_AWAY_PATH_WITH_MARKET_AWAY_PATH         "north"
#define ENVCON_HOME_AWAY_PATH_WITH_AWAY_PATH_1              "east"
#define ENVCON_AWAY_PATH_1_WITH_HOME_AWAY_PATH              "south-west"
#define ENVCON_MARKET_AWAY_PATH_WITH_AWAY_PATH_1            "south-east"
#define ENVCON_AWAY_PATH_1_WITH_MARKET_PATH                 "north-west"
#define ENVCON_AWAY_PATH_1_WITH_AWAY_PATH_2                 "east"
#define ENVCON_AWAY_PATH_2_WITH_AWAY_PATH_1                 "west"
#define ENVCON_AWAY_PATH_2_WITH_AWAY_PATH_3                 "north-east"
#define ENVCON_AWAY_PATH_3_WITH_AWAY_PATH_2                 "south-west"
#define ENVCON_AWAY_PATH_3_WITH_FOREST_PATH_1               "north-east"
#define ENVCON_FOREST_PATH_1_WITH_AWAY_PATH_3               "south-west"
#define ENVCON_FOREST_PATH_1_WITH_AWAY_CATH_PATH            "south"
#define ENVCON_AWAY_CATH_PATH_WITH_FOREST_PATH_1            "north"
#define ENVCON_AWAY_PATH_3_WITH_AWAY_CATH_PATH              "east"
#define ENVCON_AWAY_CATH_PATH_WITH_AWAY_PATH_3              "west"
#define ENVCON_AWAY_CATH_PATH_WITH_CATH_BISH_PATH           "south-east"
#define ENVCON_CATH_BISH_PATH_WITH_AWAY_CATH_PATH           "north-west"
#define ENVCON_CATH_BISH_PATH_WITH_BISH_HOUSE               "inside"
#define ENVCON_BISH_HOUSE_WITH_CATH_BISH_PATH               "outside"
#define ENVCON_BISH_HOUSE_WITH_BISH_HOUSE_SECRET            "cellar"
#define ENVCON_BISH_HOUSE_SECRET_WITH_BISH_HOUSE            "house"
#define ENVCON_CATH_BISH_PATH_WITH_CATH_PATH                "south-east"
#define ENVCON_CATH_PATH_WITH_CATH_BISH_PATH                "north-west"
#define ENVCON_CATH_PATH_WITH_CATH_HALL                     "inside"
#define ENVCON_CATH_HALL_WITH_CATH_PATH                     "outside"
#define ENVCON_CATH_HALL_WITH_CATH_WEST_WING                "left"
#define ENVCON_CATH_WEST_WING_WITH_CATH_HALL                "hall"
#define ENVCON_CATH_HALL_WITH_CATH_EAST_WING                "right"
#define ENVCON_CATH_EAST_WING_WITH_CATH_HALL                "hall"
#define ENVCON_CATH_HALL_WITH_CATH_BOSS_ROOM                "altar room"
#define ENVCON_CATH_BOSS_ROOM_WITH_CATH_HALL                "hall"
#define ENVCON_FOREST_PATH_1_WITH_GRAVEYARD_PATH            "north-west"
#define ENVCON_GRAVEYARD_PATH_WITH_FOREST_PATH_1            "south-east"
#define ENVCON_GRAVEYARD_PATH_WITH_GRAVEYARD                "graveyard"
#define ENVCON_GRAEVYARD_WITH_GRAVEYARD_PATH                "out"
#define ENVCON_FOREST_PATH_1_WITH_FOREST_PATH_2             "north-east"
#define ENVCON_FOREST_PATH_2_WITH_FOREST_PATH_1             "south-west"
#define ENVCON_FOREST_PATH_2_WITH_FOREST_ENTRANCE           "north"
#define ENVCON_FOREST_ENTRANCE_WITH_FOREST_PATH_2           "south"
#define ENVCON_FOREST_ENTRANCE_WITH_FOREST_WEST             "west"
#define ENVCON_FOREST_ENTRANCE_WITH_FOREST_NORTH            "north"
#define ENVCON_FOREST_ENTRANCE_WITH_FOREST_NORTH_EAST       "north-east"
#define ENVCON_FOREST_ENTRANCE_WITH_FOREST_EAST             "east"
#define ENVCON_FOREST_WEST_WITH_FOREST_ENTRANCE             "east"
#define ENVCON_FOREST_WEST_WITH_FOREST_NORTH                "north-east"
#define ENVCON_FOREST_NORTH_WITH_FOREST_WEST                "south-west"
#define ENVCON_FOREST_NORTH_WITH_FOREST_ENTRANCE            "south"
#define ENVCON_FOREST_NORTH_WITH_FOREST_NORTH_EAST          "east"
#define ENVCON_FOREST_NORTH_EAST_WITH_FOREST_NORTH          "west"
#define ENVCON_FOREST_NORTH_EAST_WITH_FOREST_ENTRANCE       "south-west"
#define ENVCON_FOREST_NORTH_EAST_WITH_FOREST_EAST           "south"
#define ENVCON_FOREST_EAST_WITH_FOREST_NORTH_EAST           "north"
#define ENVCON_FOREST_EAST_WITH_FOREST_ENTRANCE             "west"


//---- Player and Character----

#define PLAYER_NAME                         "McLovin'"
#define PLAYER_HEALTH                       100
#define PLAYER_BASE_ARMOR                   0
#define PLAYER_BASE_DODGE                   5
#define PLAYER_BASE_BLOCK                   0
#define PLAYER_BASE_MIN_DMG                 20
#define PLAYER_BASE_MAX_DMG                 60
#define PLAYER_BASE_CRIT_PROB               5
#define PLAYER_BASE_CRIT_MOD                50

#define CHARACTER_HEALTH                    300
#define CHARACTER_BASE_ARMOR                50
#define CHARACTER_BASE_DODGE                5
#define CHARACTER_BASE_BLOCK                0
#define CHARACTER_BASE_MIN_DMG              15
#define CHARACTER_BASE_MAX_DMG              25
#define CHARACTER_BASE_CRIT_PROB            5
#define CHARACTER_BASE_CRIT_MOD             50
#define CHARACTER_INVENTORY_SIZE            50

//---- Monsters ----

#define MONSTER_BASE_ARMOR                  0
#define MONSTER_BASE_DODGE                  5
#define MONSTER_BASE_BLOCK                  0
#define MONSTER_BASE_MIN_DMG                25
#define MONSTER_BASE_MAX_DMG                50
#define MONSTER_BASE_CRIT_PROB              10
#define MONSTER_BASE_CRIT_MOD               50

#define CHARACTER_TYPE_RAT                  "Rat"
#define RAT_HEALTH                          50
#define RAT_BASE_ARMOR                      0
#define RAT_BASE_DODGE                      25
#define RAT_BASE_BLOCK                      0
#define RAT_BASE_MIN_DMG                    1
#define RAT_BASE_MAX_DMG                    25
#define RAT_BASE_CRIT_PROB                  15
#define RAT_BASE_CRIT_MOD                   100
#define RAT_MOVE_PROB                       80
#define RAT_ATTACK_PROB                     50

#define CHARACTER_TYPE_TROLL                "Troll"
#define TROLL_HEALTH                        500
#define TROLL_BASE_ARMOR                    25
#define TROLL_BASE_DODGE                    5
#define TROLL_BASE_BLOCK                    20
#define TROLL_BASE_MIN_DMG                  50
#define TROLL_BASE_MAX_DMG                  150
#define TROLL_BASE_CRIT_PROB                25
#define TROLL_BASE_CRIT_MOD                 150
#define TROLL_MOVE_PROB                     30
#define TROLL_ATTACK_PROB                   80

#define CHARACTER_TYPE_OGRE                 "Ogre"
#define OGRE_HEALTH                         650
#define OGRE_BASE_ARMOR                     50
#define OGRE_BASE_DODGE                     0
#define OGRE_BASE_BLOCK                     30
#define OGRE_BASE_MIN_DMG                   100
#define OGRE_BASE_MAX_DMG                   250
#define OGRE_BASE_CRIT_PROB                 25
#define OGRE_BASE_CRIT_MOD                  150
#define OGRE_MOVE_PROB                      10
#define OGRE_ATTACK_PROB                    90

#define CHARACTER_TYPE_GHOST                "Ghost"
#define GHOST_HEALTH                        100
#define GHOST_BASE_ARMOR                    100
#define GHOST_BASE_DODGE                    50
#define GHOST_BASE_BLOCK                    0
#define GHOST_BASE_MIN_DMG                  1
#define GHOST_BASE_MAX_DMG                  250
#define GHOST_BASE_CRIT_PROB                5
#define GHOST_BASE_CRIT_MOD                 50
#define GHOST_MOVE_PROB                     40
#define GHOST_ATTACK_PROB                   100

#define CHARACTER_TYPE_VAMPIRE              "Vampire"
#define VAMPIRE_HEALTH                      1000
#define VAMPIRE_BASE_ARMOR                  0
#define VAMPIRE_BASE_DODGE                  10
#define VAMPIRE_BASE_BLOCK                  0
#define VAMPIRE_BASE_MIN_DMG                250
#define VAMPIRE_BASE_MAX_DMG                400
#define VAMPIRE_BASE_CRIT_PROB              5
#define VAMPIRE_BASE_CRIT_MOD               100
#define VAMPIRE_MOVE_PROB                   5
#define VAMPIRE_ATTACK_PROB                 100

#define CHARACTER_TYPE_DEMON                "Demon"
#define DEMON_HEALTH                        2500
#define DEMON_BASE_ARMOR                    700
#define DEMON_BASE_DODGE                    5
#define DEMON_BASE_BLOCK                    30
#define DEMON_BASE_MIN_DMG                  1000
#define DEMON_BASE_MAX_DMG                  2000
#define DEMON_BASE_CRIT_PROB                10
#define DEMON_BASE_CRIT_MOD                 50
#define DEMON_MOVE_PROB                     0
#define DEMON_ATTACK_PROB                   100

#define CHARACTER_TYPE_BOSS                 "Boss"
#define DEMON_BOSS_NAME                     "Malphas"
#define DEMON_BOSS_HEALTH                   5000
#define DEMON_BOSS_BASE_ARMOR               1000
#define DEMON_BOSS_BASE_DODGE               5
#define DEMON_BOSS_BASE_BLOCK               15
#define DEMON_BOSS_BASE_MIN_DMG             2000
#define DEMON_BOSS_BASE_MAX_DMG             4000
#define DEMON_BOSS_BASE_CRIT_PROB           10
#define DEMON_BOSS_BASE_CRIT_MOD            100
#define DEMON_BOSS_MOVE_PROB                0
#define DEMON_BOSS_ATTACK_PROB              10


#endif
