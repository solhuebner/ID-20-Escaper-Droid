#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

struct EscaperDroid
{
  public:
    int x, y;
    byte life;
    byte characteristics = 0b00000000;      //this byte holds all the Escaperdroids characteristics
    //                       ||||||||
    //                       |||||||└->  0  | this 2 bits are used for direction
    //                       ||||||└-->  1  | 00 = NORTH / 01 = EAST / 10 = SOUTH / 11 = WEST
    //                       |||||└--->  2  The droid is visible               (0 = false / 1 = true)
    //                       ||||└---->  3  The droid is imune                 (0 = false / 1 = true)
    //                       |||└----->  4  The droid is dying                 (0 = false / 1 = true)
    //                       ||└------>  5  The droid is going through a door  (0 = false / 1 = true)
    //                       |└------->  6  The droid is coming out a door     (0 = false / 1 = true)
    //                       └-------->  7
    byte imuneTimer;
    byte steps;

    void set()
    {
      
      /*
      bitClear (characteristics, 6);        // The droid is coming out a door      = false
      bitClear (characteristics, 5);        // The droid is going Through a door   = false
      bitClear (characteristics, 4);        // The droid is dying                  = false
      bitClear (characteristics, 3);        // The droid is imune                  = false
      bitSet (characteristics, 2);          // The droid is visible                = false
      bitClear (characteristics, 0);        // | The droid is facing SOUTH
      bitSet (characteristics, 1);          // |
      */
      characteristics = 0b00000110;
      imuneTimer = 60;
      steps = 0;
      life = 3;
    }
};

EscaperDroid player;


void walkThroughDoor()
{
  if (bitRead(player.characteristics, 5) || bitRead(player.characteristics, 6)) player.steps++;
  switch (player.characteristics & 0b00000011)
  {
    case NORTH:
      if (currentRoomY < 0) currentRoomY++;
      else player.y -= 1;
      player.x -= 2;
      break;
    case EAST:
      if (currentRoomY < 0)currentRoomY++;
      else player.y -= 1;
      player.x += 2;
      break;
    case SOUTH:
      if (currentRoomY > -30)currentRoomY--;
      else player.y += 1;
      player.x += 2;
      break;
    case WEST:
      if (currentRoomY > -30)currentRoomY--;
      else player.y += 1;
      player.x -= 2;
      break;
  }
}


void drawPlayer()
{
  if (bitRead(player.characteristics, 2))
  {
    sprites.drawPlusMask(player.x, player.y, droid_plus_mask, player.characteristics & 0b00000011);
  }
}

#endif
