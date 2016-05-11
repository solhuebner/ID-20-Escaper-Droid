#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arglib.h"
#include "bitmaps.h"

// constants /////////////////////////////////////////////////////////////////

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_INFO          4
#define STATE_MENU_SOUNDFX       5

//define game states (on main menu)
#define STATE_GAME_PLAYING       6
#define STATE_GAME_PAUSE         7
#define STATE_GAME_OVER          8

//define facing directions
#define NORTH                    0
#define EAST                     1
#define SOUTH                    2
#define WEST                     3

#define NORTH_SOUTH              0
#define EAST_WEST                1

// globals ///////////////////////////////////////////////////////////////////

Arduboy arduboy;
Sprites sprites(arduboy);
SimpleButtons buttons(arduboy);
unsigned long scorePlayer;
boolean soundYesNo;
byte gameState  = 1;;
byte counter = 0;

int menuSelection;
byte currentRoom;
int currentRoomY;
byte level;
byte selectorX = 17;
byte selectorX2 = 35;
byte tile;
#endif
