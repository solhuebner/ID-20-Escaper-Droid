#ifndef INPUTS_H
#define INPUTS_H

#include "globals.h"
#include "player.h"
#include "collision.h"
#include "elements.h"


void checkInputs()
{
  if (arduboy.everyXFrames(2))
  {
    if (arduboy.pressed(UP_BUTTON))
    {
      bitClear(player.characteristics, 0);
      bitClear(player.characteristics, 1);
      if (!checkborderHit(player.x, player.y, NORTH))
      {
        if (hitObjects(player.x, player.y - currentRoomY, NORTH))
        {
          decideOnCollision();
        }
        else walkThroughDoor();
      }
    }


    else if (arduboy.pressed(RIGHT_BUTTON))
    {
      bitSet(player.characteristics, 0);
      bitClear(player.characteristics, 1);
      if (!checkborderHit(player.x, player.y, EAST))
      {
        if (hitObjects(player.x, player.y - currentRoomY, EAST))
        {
          decideOnCollision();
        }
        else walkThroughDoor();
      }
    }

    else if (arduboy.pressed(DOWN_BUTTON))
    {
      bitClear(player.characteristics, 0);
      bitSet(player.characteristics, 1);
      if (!checkborderHit(player.x, player.y, SOUTH))
      {
        if (hitObjects(player.x, player.y - currentRoomY, SOUTH))
        {
          decideOnCollision();
        }
        else walkThroughDoor();
      }
    }

    else if (arduboy.pressed(LEFT_BUTTON))
    {
      bitSet(player.characteristics, 0);
      bitSet(player.characteristics, 1);
      if (!checkborderHit(player.x, player.y, WEST))
      {
        if (hitObjects(player.x, player.y - currentRoomY, WEST))
        {
          decideOnCollision();
        }
        else walkThroughDoor();
      }
    }
  }

  if (arduboy.justPressed(A_BUTTON))gameState = STATE_GAME_PAUSE;
  if (arduboy.justPressed(B_BUTTON))
  {

  }
}



////Moving the Enemies /////
////////////////////////////
void moveEnemies(int enemyX, int enemyY, byte directionFacing, bool enemy)
{
  if (arduboy.everyXFrames(4))
  {
    switch (directionFacing)
    {
      case NORTH:
        elements[enemy].y -= 1;
        elements[enemy].x -= 2;
        break;
      case EAST:
        elements[enemy].y -= 1;
        elements[enemy].x += 2;
        break;
      case SOUTH:
        elements[enemy].y += 1;
        elements[enemy].x += 2;
        break;
      case WEST:
        elements[enemy].y += 1;
        elements[enemy].x -= 2;
        break;
    }
  }
}


void updateEnemies()
{
  byte i = 0;
  while (i < 2)
  {
    switch (elements[i].characteristics & 0b00000111)
    {
      case ENEMY_BOX:
        if (!hitBorders(elements[i].x, elements[i].y, (elements[i].characteristics & 0b00011000) >> 3, ENEMY))
        {
          moveEnemies(elements[i].x, elements[i].y, (elements[i].characteristics & 0b00011000) >> 3, i);
        }
        else
        {
          byte test = ((elements[i].characteristics & 0b00011000) >> 3) + 1;
          if (test > 3) test = 0;
          elements[i].characteristics = (elements[i].characteristics & 0b11100111) + (test << 3);
          /*
            switch ((elements[i].characteristics & 0b00011000) >> 3)
            {
            case NORTH:
              elements[i].characteristics = (elements[i].characteristics & 0b11100111) + 0b00010000; // 2
              break;
            case EAST:
              elements[i].characteristics = (elements[i].characteristics & 0b11100111) + 0b00011000; // 3
              break;
            case SOUTH:
              elements[i].characteristics = (elements[i].characteristics & 0b11100111) + 0b00000000; // 0
              break;
            case WEST:
              elements[i].characteristics = (elements[i].characteristics & 0b11100111) + 0b00001000; // 1
              break;
            }
            /*
            byte test = (elements[i].characteristics & 0b00011000) >> 3;
            for (byte i = 0; i< 2; i++)
            {
            test++;
            if (test > 3)
            test = 0;
            }
            elements[i].characteristics = (elements[i].characteristics & 0b11100111) + (test << 3);
          */
        }
        break;
      case ENEMY_SPHERE:
        break;
      case ENEMY_JUMPER:
        break;
      case ENEMY_MOVER:
        break;
    }
    i++;
  }
}

#endif
