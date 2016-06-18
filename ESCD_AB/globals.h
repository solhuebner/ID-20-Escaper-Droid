#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arglib.h"
#include "bitmaps.h"

// constants /////////////////////////////////////////////////////////////////

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_HELP              2
#define STATE_MENU_PLAY              3
#define STATE_MENU_INFO              4
#define STATE_MENU_SOUNDFX           5

//define game states (on main menu)
#define STATE_GAME_PLAYING           6
#define STATE_GAME_NEXT_ROOM         7
#define STATE_GAME_NEXT_LEVEL        8
#define STATE_GAME_PAUSE             9
#define STATE_GAME_OVER              10

//define facing directions
#define NORTH                        0
#define EAST                         1
#define SOUTH                        2
#define WEST                         3

#define NORTH_SOUTH                  0
#define EAST_WEST                    1

#define SMALL_FONT                   0
#define BIG_FONT                     1

#define LEVEL_TO_START_WITH          1

// globals ///////////////////////////////////////////////////////////////////

Arduboy arduboy;
Sprites sprites(arduboy);

byte gameState = STATE_MENU_INTRO;   // start the game with the TEAM a.r.g. logo
byte menuSelection = STATE_MENU_PLAY; // PLAY menu item is pre-selected
byte globalCounter = 0;
byte level = LEVEL_TO_START_WITH;
unsigned long scorePlayer; 

byte currentRoom;
int currentRoomY;
byte selectorX = 17;
byte selectorX2 = 35;
byte tile;
#endif
