#ifndef INPUTS_H
#define INPUTS_H

#define ENEMY                    0
#define PLAYER                   1


#include "globals.h"
#include "player.h"
#include "collision.h"


boolean canGoTroughDoor(byte x, byte y)
{
  return false;
}

void checkInputs()
{
  if (arduboy.pressed(UP_BUTTON))
  {
    bitClear(player.characteristics, 0);
    bitClear(player.characteristics, 1);
    if (!hitNorthBorder(player.x, player.y)) droidWalkNorth();
  }

  
  if (arduboy.pressed(RIGHT_BUTTON))
  {
    bitSet(player.characteristics, 0);
    bitClear(player.characteristics, 1);
    if (!hitEastBorder(player.x, player.y)) droidWalkEast();
  }
  
  if (arduboy.pressed(DOWN_BUTTON))
  {
    bitClear(player.characteristics, 0);
    bitSet(player.characteristics, 1);
    if (!hitSouthBorder(player.x, player.y)) droidWalkSouth();
  }
  if (arduboy.pressed(LEFT_BUTTON))
  {
    bitSet(player.characteristics, 0);
    bitSet(player.characteristics, 1);
    if (!hitWestBorder(player.x, player.y)) droidWalkWest();
  }

  if (arduboy.justPressed(A_BUTTON))gameState = STATE_GAME_PAUSE;
  if (arduboy.justPressed(B_BUTTON));
}

#endif
