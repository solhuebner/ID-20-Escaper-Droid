#ifndef INPUTS_H
#define INPUTS_H

#include "globals.h"
#include "player.h"
#include "collision.h"


void checkInputs()
{
  if (arduboy.everyXFrames(2))

  {
    if (arduboy.pressed(UP_BUTTON))
    {
      bitClear(player.characteristics, 0);
      bitClear(player.characteristics, 1);
      if (!hitNorthBorder(player.x, player.y))
      {
        if (hitObjects(player.x, player.y - currentRoomY, NORTH));
        else walkThroughDoor();
      }
    }


    if (arduboy.pressed(RIGHT_BUTTON))
    {
      bitSet(player.characteristics, 0);
      bitClear(player.characteristics, 1);
      if (!hitEastBorder(player.x, player.y))
      {
        if (hitObjects(player.x, player.y - currentRoomY, EAST));
        else walkThroughDoor();
      }
    }

    if (arduboy.pressed(DOWN_BUTTON))
    {
      bitClear(player.characteristics, 0);
      bitSet(player.characteristics, 1);
      if (!hitSouthBorder(player.x, player.y))
      {
        if (hitObjects(player.x, player.y - currentRoomY, SOUTH));
        else walkThroughDoor();
      }
    }
    if (arduboy.pressed(LEFT_BUTTON))
    {
      bitSet(player.characteristics, 0);
      bitSet(player.characteristics, 1);
      if (!hitWestBorder(player.x, player.y))
      {
        if (hitObjects(player.x, player.y - currentRoomY, WEST));
        else walkThroughDoor();
      }
    }
  }

  if (arduboy.justPressed(A_BUTTON))gameState = STATE_GAME_PAUSE;
  if (arduboy.justPressed(B_BUTTON))
  {

  }
}

#endif
