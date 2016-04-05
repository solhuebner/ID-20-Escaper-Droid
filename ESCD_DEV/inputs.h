#ifndef INPUTS_H
#define INPUTS_H

#define ENEMIE                   0
#define PLAYER                   1


#include "globals.h"
#include "player.h"
#include "collision.h"

extern Arduboy arduboy;
extern SimpleButtons buttons;
extern byte currentRoom;
extern unsigned char gameState;
extern int currentRoomY;



boolean canGoTroughDoor(byte x, byte y)
{
  return false;
}

void checkInputs()
{
  if (buttons.pressed(UP_BUTTON))
  {
    bitClear(player.characteristics, 0);
    bitClear(player.characteristics, 1);
    if (northBorder(player.x, player.y))
    {
      if (currentRoomY < 0) currentRoomY++;
      else player.y -= 1;
      player.x -= 2;
    }
  }
  if (buttons.pressed(RIGHT_BUTTON))
  {
    bitSet(player.characteristics, 0);
    bitClear(player.characteristics, 1);
    if (eastBorder(player.x, player.y))
    {
      if (currentRoomY < 0)currentRoomY++;
      else player.y -= 1;
      player.x += 2;
    }
    

  }
  if (buttons.pressed(DOWN_BUTTON))
  {
    bitClear(player.characteristics, 0);
    bitSet(player.characteristics, 1);
    if (southBorder(player.x, player.y))
    {
      if (currentRoomY > -30)currentRoomY--;
      else player.y += 1;
      player.x += 2;
    }
  }
  if (buttons.pressed(LEFT_BUTTON))
  {
    bitSet(player.characteristics, 0);
    bitSet(player.characteristics, 1);
    if (westBorder(player.x, player.y))
    {
      if (currentRoomY > -30)currentRoomY--;
      else player.y += 1;
      player.x -= 2;
    }
  }


  if (buttons.justPressed(A_BUTTON))gameState = STATE_GAME_PAUSE;
  if (buttons.justPressed(B_BUTTON));
}

#endif
