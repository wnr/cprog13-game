#ifndef cprog13_game_Constants_h
#define cprog13_game_Constants_h

#define CERR_LOG                            true

#define MAXIMUM_ROTTENNESS                  5

#define OBJECT_TYPE_ENVIRONMENT             "Environment"
#define OBJECT_TYPE_GRAVEYARD_ENVIRONMENT   "Graveyard"
#define OBJECT_TYPE_CONTAINER               "Container"
#define OBJECT_TYPE_ITEM                    "Item"
#define OBJECT_TYPE_CHARACTER               "Character"

#define CHARACTER_TYPE_PLAYER               "Player"
#define CHARACTER_TYPE_MONSTER              "Monster"
#define CHARACTER_INVENTORY_SIZE            50

#define ITEM_TYPE_WEAPON                    "Weapon"
#define ITEM_TYPE_KEY                       "Key"
#define ITEM_TYPE_FOOD                      "Food"

#define CONTAINER_TYPE_BACKPACK             "Backpack"
#define CONTAINER_TYPE_CHEST                "Chest"

#define KEY_STANDARD_IDENTIFIER             "Standard_key"
#define KEY_STANDARD_LEVEL                  3

#define WEAPON_CRIT_PROB                    2
#define WEAPON_CRIT_MOD                     1.5

#define FOOD_STRENGTH                       10
#define FOOD_WEIGHT                         3

#define LIST_ITEM_PREFIX                    "* "
#define INPUT_WORD_DELIMETER                " "
#define INPUT_INDICATOR                     "> "
#define INPUT_INVALID_COMMAND               "Invalid command. Type 'help' for command instructions."
#define INFORMATION_UNKNOWN                 "?"

#define GAME_INTRO                          "This is a magical game with magic and stuff. Type 'exit' to exit, otherwise just follow the instructions."
#define GAME_OUTRO                          ""

#define TEXT_DIVIDER                        "----------"
#define HELP_TEXT                           "To move somewhere, type 'goto' or 'go' or 'move' followed by a direction. Example: 'go outside'\nTo quit the time, type 'exit'"


#define CHARACTER_TYPE_GHOST                "Ghost"
#define GHOST_HEALTH                        500
#define GHOST_MOVE_PROB                     35
#define GHOST_ATTACK_PROB                   60

#define CHARACTER_TYPE_TROLL                "Troll"
#define TROLL_HEALTH                        100
#define TROLL_MOVE_PROB                     50
#define TROLL_ATTACK_PROB                   70

#define CHARACTER_TYPE_DEMON                "Demon"
#define DEMON_HEALTH                        10000
#define DEMON_MOVE_PROB                     0
#define DEMON_ATTACK_PROB                   100


#endif
