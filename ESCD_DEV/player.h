#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"


//define facing directions
#define NORTH                    0
#define EAST                     1
#define SOUTH                    2
#define WEST                     3

extern Arduboy arduboy;
extern Sprites sprites;
extern int currentRoomY;

struct EscaperDroid
{
  public:
    int x, y;
    byte characteristics = 0b00000100;   //this byte holds all the Escaperdroids characteristics
    //                       ||||||||
    //                       |||||||└->  | this 2 bits are used for direction
    //                       ||||||└-->  | 00 = NORTH / 01 = EAST / 10 = SOUTH / 11 = WEST
    //                       |||||└--->  Show the droid       (0 = false / 1 = true)
    //                       ||||└---->  The droid is imune   (0 = false / 1 = true)
    //                       |||└----->  The droid is dying   (0 = false / 1 = true)
    //                       ||└------>  
    //                       |└------->  
    //                       └-------->  
    byte imuneTimer;

    void reset()
    {
      x = 23;
      y = 24;
      imuneTimer = 60;

    }
};

EscaperDroid player;

void drawPlayer()
{
  if (bitRead(player.characteristics,2))
  {
    sprites.drawBitmap( player.x, player.y, droidPlusMask[player.characteristics & 0b00000011], NULL, 16, 24, SPRITE_PLUS_MASK);
  }
}

#endif
