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


#endif