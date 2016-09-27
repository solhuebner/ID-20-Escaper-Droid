#ifndef COLLISION_H
#define COLLISION_H

#include "globals.h"

boolean hitNorthBorder(int objectX, int objectY)
{
  // check the border of the room

  if (objectX + (2 * objectY) > 89 + (2 * currentRoomY))return false;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 2) &&             // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 7)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 3))           // the door is not closed
       )
    {
      bitSet (player.characteristics, 5);                                  // if all above, set the droid is walking through the door
      player.x = translateTileToX(2);
      player.y = translateTileToY(2) + currentRoomY;
    }
    return true;
  }
}

boolean hitEastBorder(int objectX, int objectY)
{
  // check the border of the room
  if (objectX - (2 * objectY) < 15 - (2 * currentRoomY)) return false;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 10) &&            // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 6)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 2))           // the door is not closed
       )
    {
      bitSet (player.characteristics, 5);                                 // if all above, set the droid is walking through the door
      player.x = translateTileToX(10);
      player.y = translateTileToY(10) + currentRoomY;
    }
    return true;
  }
}

boolean hitSouthBorder(int objectX, int objectY)
{
  // check the border of the room
  if (objectX + (2 * objectY) < 183 + (2 * currentRoomY)) return false;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 22) &&            // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 5)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 1))           // the door is not closed
       )
    {
      bitSet (player.characteristics, 5);                                 // if all above, set the droid is walking through the door
      player.x = translateTileToX(22);
      player.y = translateTileToY(22) + currentRoomY;
    }
    return true;
  }
}

boolean hitWestBorder(int objectX, int objectY)
{
  // check the border of the room
  if (objectX - (2 * objectY) > -81 - (2 * currentRoomY)) return false;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 14) &&            // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 4)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 0))           // the door is not closed
       )
    {
      bitSet (player.characteristics, 5);                                 // if all above, set the droid is walking through the door
      player.x = translateTileToX(14);
      player.y = translateTileToY(14) + currentRoomY;
    }
    return true;
  }
}

boolean tileIsOccupied(byte tileTesting)
{
  currentlyOnTestingTile = itemsOrder[tileTesting + ITEMS_ORDER_TILES_START];
  Serial.print("tile ");
  Serial.print(tileTesting);
  Serial.print(" has ");
  Serial.println(currentlyOnTestingTile);
  if ((currentlyOnTestingTile == PLAYER_DROID) || (currentlyOnTestingTile == EMPTY_PLACE)) return false;
  else return true;
}


boolean hitObjects (int objectX, int objectY, byte directionFacing)
{
  switch (directionFacing)
  {
    case NORTH:
      testingTile = tileFromXY(objectX - 8, objectY - 4);
      Serial.println(testingTile);
      if (tileIsOccupied(testingTile)) return true;
      else return false;
      break;
    case EAST:
      testingTile = tileFromXY(objectX + 8, objectY - 4);
      Serial.println(testingTile);
      if (tileIsOccupied(testingTile)) return true;
      else return false;
      break;
    case SOUTH:
      testingTile = tileFromXY(objectX + 6, objectY + 3);
      Serial.println(testingTile);
      if (tileIsOccupied(testingTile)) return true;
      else return false;
      break;
    case WEST:
      testingTile = tileFromXY(objectX - 6, objectY + 3);
      Serial.println(testingTile);
      if (tileIsOccupied(testingTile)) return true;
      else return false;
      break;
  }
}

void checkObjectTypeAndAct()
{
  
  bitClear(stageRoom[currentRoom].enemiesActive, 5);
}


void decideOnCollision()
{
  Serial.print("testing : ");
  Serial.print(testingTile);
  switch (currentlyOnTestingTile)
  {
    case ENEMY_ONE:
      break;
    case ENEMY_TWO:
      break;
    case OBJECT_THREE:
      Serial.print(" switching");
      checkObjectTypeAndAct();
      //itemsOrder[testingTile + ITEMS_ORDER_TILES_START] = 0;
      break;
    case FLOOR_ONE:
      break;
    case FLOOR_TWO:
      break;
    case FLOOR_THREE:
      break;
    case FLOOR_FOUR:
      break;
    case FLOOR_FIVE:
      break;

  }
}


#endif
