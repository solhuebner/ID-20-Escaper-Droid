#ifndef COLLISION_H
#define COLLISION_H

#include "globals.h"

boolean northBorder(int objectX, int objectY)
{
  // check the border of the room

  if (objectX + (2 * objectY) > 89 + (2 * currentRoomY))return true;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 2) &&             // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 7)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 3))           // the door is not closed
       ) bitSet (player.characteristics, 5);                              // if all above, set the droid is walking through the door
    return false;
  }
}

boolean eastBorder(int objectX, int objectY)
{
  // check the border of the room
  if (objectX - (2 * objectY) < 15 - (2 * currentRoomY)) return true;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 10) &&            // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 6)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 2))           // the door is not closed
       ) bitSet (player.characteristics, 5);                              // if all above, set the droid is walking through the door
    return false;
  }
}

boolean southBorder(int objectX, int objectY)
{
  // check the border of the room
  if (objectX + (2 * objectY) < 183 + (2 * currentRoomY)) return true;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 22) &&            // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 5)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 1))           // the door is not closed
       ) bitSet (player.characteristics, 5);                              // if all above, set the droid is walking through the door
    return false;
  }
}

boolean westBorder(int objectX, int objectY)
{
  // check the border of the room
  if (objectX - (2 * objectY) > -81 - (2 * currentRoomY)) return true;
  else
  {
    if ((tileFromXY(objectX, objectY - currentRoomY) == 14) &&            // droid is on the tile for a door
        (bitRead(stageRoom[currentRoom].doorsClosedActive, 4)) &&         // the door exists in this room
        (!bitRead(stageRoom[currentRoom].doorsClosedActive, 0))           // the door is not closed
       ) bitSet (player.characteristics, 5);                              // if all above, set the droid is walking through the door
    return false;
  }
}


#endif
