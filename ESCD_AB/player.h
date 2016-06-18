#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

struct EscaperDroid
{
  public:
    byte x, y;
    byte life;
    byte characteristics = 0b00000100;      //this byte holds all the Escaperdroids characteristics
    //                       ||||||||
    //                       |||||||└->  0  | this 2 bits are used for direction
    //                       ||||||└-->  1  | 00 = NORTH / 01 = EAST / 10 = SOUTH / 11 = WEST
    //                       |||||└--->  2  The droid is visible               (0 = false / 1 = true)
    //                       ||||└---->  3  The droid is imune                 (0 = false / 1 = true)
    //                       |||└----->  4  The droid is dying                 (0 = false / 1 = true)
    //                       ||└------>  5  The droid is going Through a door  (0 = false / 1 = true)
    //                       |└------->  6
    //                       └-------->  7
    byte imuneTimer;
    byte steps;

    void set()
    {
      bitClear (characteristics, 5);        //The droid is going Through a door   = false
      bitClear (characteristics, 4);        //The droid is dying                  = false
      bitClear (characteristics, 3);        //The droid is imune                  = false
      bitSet (characteristics, 2);          //The droid is visible                = false
      imuneTimer = 60;
      steps = 0;
    }

    void reset()
    {
      x = 23;
      y = 24;
      imuneTimer = 60;
      life = 3;
      steps = 0;
    }
};

EscaperDroid player;


void droidWalkNorth()
{
  if (currentRoomY < 0) currentRoomY++;
  else player.y -= 1;
  player.x -= 2;
}

void droidWalkEast()
{
  if (currentRoomY < 0)currentRoomY++;
  else player.y -= 1;
  player.x += 2;
}

void droidWalkSouth()
{
  if (currentRoomY > -30)currentRoomY--;
  else player.y += 1;
  player.x += 2;
}

void droidWalkWest()
{
  if (currentRoomY > -30)currentRoomY--;
  else player.y += 1;
  player.x -= 2;
}


void walkThroughDoor()
{
  player.steps++;
  if ((player.characteristics & 0b00000011) == NORTH)
  {
    droidWalkNorth();
  }
  if ((player.characteristics & 0b00000011) == EAST)
  {
    droidWalkEast();
  }
  if ((player.characteristics & 0b00000011) == SOUTH)
  {
    droidWalkSouth();
  }
  if ((player.characteristics & 0b00000011) == WEST)
  {
    droidWalkWest();
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
