#ifndef ROOM_H
#define ROOM_H

#include "globals.h"
#include "levels.h"
#include "player.h"
#include "enemies.h"

#define NORTH_LINTEL                  11
#define NORTH_BIG_POST                12
#define NORTH_SMALL_POST              13
#define NORTH_DOOR_CLOSSED            14

#define EAST_LINTEL                   15
#define EAST_BIG_POST                 16
#define EAST_SMALL_POST               17
#define EAST_DOOR_CLOSSED             18

#define SOUTH_LINTEL                  19
#define SOUTH_BIG_POST                20
#define SOUTH_SMALL_POST              21
#define SOUTH_DOOR_CLOSSED            22

#define WEST_LINTEL                   23
#define WEST_BIG_POST                 24
#define WEST_SMALL_POST               25
#define WEST_DOOR_CLOSSED             26

#define EMPTY_PLACE                   27



//define how collision works
#define DIFF(A, B) (((A) > (B)) ? ((A) - (B)) : ((B) - (A)))

//byte doorsX[4] = {16, 80, 81, 14};
//byte doorsY[4] = {5, 5, 38, 38};
//byte lifeVisible = true;


struct Room {
  public:
    byte doorsClosedActive = 0b00000000;   // this byte holds all the 4 doors characteristics for each room
    //                         ||||||||
    //                         |||||||└->  0  DOOR WEST  IS CLOSED (0 = false / 1 = true)
    //                         ||||||└-->  1  DOOR SOUTH IS CLOSED (0 = false / 1 = true)
    //                         |||||└--->  2  DOOR EAST  IS CLOSED (0 = false / 1 = true)
    //                         ||||└---->  3  DOOR NORTH IS CLOSED (0 = false / 1 = true)
    //                         |||└----->  4  DOOR WEST  EXISTS    (0 = false / 1 = true)
    //                         ||└------>  5  DOOR SOUTH EXISTS    (0 = false / 1 = true)
    //                         |└------->  6  DOOR EAST  EXISTS    (0 = false / 1 = true)
    //                         └-------->  7  DOOR NORTH EXISTS    (0 = false / 1 = true)

    byte enemiesActive = 0b00000000;
    //                     ||||||||
    //                     |||||||└->  7 => 0 FLOOR  5 EXISTS (0 = false / 1 = true)
    //                     ||||||└-->  6 => 1 FLOOR  4 EXISTS (0 = false / 1 = true)
    //                     |||||└--->  5 => 2 FLOOR  3 EXISTS (0 = false / 1 = true)
    //                     ||||└---->  4 => 3 FLOOR  2 EXISTS (0 = false / 1 = true)
    //                     |||└----->  3 => 4 FLOOR  1 EXISTS (0 = false / 1 = true)
    //                     ||└------>  2 => 5 OBJECT 3 EXISTS (0 = false / 1 = true)
    //                     |└------->  1 => 6 ENEMY  2 EXISTS (0 = false / 1 = true)
    //                     └-------->  0 => 7 ENEMY  1 EXISTS (0 = false / 1 = true)
};

Room stageRoom[MAX_AMOUNT_OF_ROOMS];

void buildRooms(byte currentLevel)
{
  for (byte roomNumber = 0; roomNumber < pgm_read_byte(&levels[currentLevel - 1][0]); roomNumber++)
  {
    //clear all info
    stageRoom[roomNumber].doorsClosedActive = 0;
    stageRoom[roomNumber].enemiesActive = 0;
    stageRoom[roomNumber].doorsClosedActive = pgm_read_byte(&levels[currentLevel - 1][1 + (13 * roomNumber)]);
    for (byte i = 0; i < 8; i++)
    {
      if (pgm_read_byte(&levels[currentLevel - 1][1 + 5 + i + (13 * roomNumber)]))
      { //0b76543210
        bitSet (stageRoom[roomNumber].enemiesActive, 7 - i);    //0b12345678
      }
      //Serial.print(pgm_read_byte(&levels[currentLevel - 1][1 + 5 + i + (13 * roomNumber)]), BIN);
      //Serial.print(" : ");
    }
    //Serial.println();
    //Serial.println(stageRoom[roomNumber].enemiesActive, BIN);
  }
  //Serial.println();
}


byte tileFromXY(byte x, byte y)
{
  unsigned int x45 = x * 170;
  unsigned int y45 = y * 341;
  x = (((y45 - x45) >> 8) + 18);
  y = (((y45 + x45) >> 8) - 49);
  return (y >> 4) * 5 + (x >> 4);
}


bool isoCollide(byte ax, byte ay, byte bx, byte by, byte max)
{
  return (DIFF(ax, bx) + DIFF(ay, by)) < max;
}


int translateTileToX (byte currentTile)
{
  return ((((((currentTile / 5) * 6) + 4) - currentTile) * 12) + 3);
}


int translateTileToY (byte currentTile)
{
  return (18 + (currentTile * 6) - ((currentTile / 5) * 24));
}



void enterRoom(byte roomNumber, byte currentLevel)
{
  for (byte i = 0; i < 8; i++)
  {
    // set all enemies at there position
    //Serial.print(bitRead (stageRoom[roomNumber].enemiesActive, 7 - i));
    //if (bitRead (stageRoom[roomNumber].enemiesActive, 7 - i))
    {
      enemy[i].isVisible  = true;
      // set enemy on correct place 0 => 24)
      byte currentTile = (pgm_read_byte(&levels[currentLevel - 1][6 + i + (13 * roomNumber)])) >> 3;
      //Serial.println((pgm_read_byte(&levels[currentLevel - 1][6 + i + (13 * roomNumber)])) >> 3);
      enemy[i].x = translateTileToX(currentTile);
      enemy[i].y = translateTileToY(currentTile);

      // first clear the characteristics
      enemy[i].characteristics = 0;
      // get kind of sprite (stored in level data) and put it into the 3 most left bits
      enemy[i].characteristics = ((pgm_read_byte(&levels[currentLevel - 1][6 + i + (13 * roomNumber)])) & 0b00000111) << 5;
      //Serial.println(enemy[i].characteristics, BIN);
      // we will always set the current direction to SOUTH (0b00000010)
      bitSet (enemy[i].characteristics, 1);

      //set the enemy hurt/movable/pickup

    }
  }
  //Serial.println();
}


byte goToRoom(byte roomNumber, byte currentLevel)
{
  // we now which door the player goes through by the direction the droid is facing
  byte door = player.characteristics & 0b00000011;
  return (pgm_read_byte(&levels[currentLevel - 1][1 + 1 + door + (13 * roomNumber)]) >> 2);
};


byte goToTile(byte roomNumber, byte currentLevel)
{
  // we now which door the player goes through by the direction the droid is facing
  byte door = player.characteristics & 0b00000011;
  byte doorGoingTo = pgm_read_byte(&levels[currentLevel - 1][1 + 1 + door + (13 * roomNumber)]) & 0b00000011;
  switch (doorGoingTo)
  {
    case NORTH:
      return 2;
      break;
    case EAST:
      return 10;
      break;
    case SOUTH:
      return 22;
      break;
    case WEST:
      return 14;
      break;
  }
}

int setCurrentRoomY(byte currentTile)
{
  switch (currentTile)
  {
    case 2:
      return -9;
      break;
    case 10:
      return -9;
      break;
    case 14:
      return -35;
      break;
    case 22:
      return -35;
      break;
  }
}

int offsetXAfterDoor(byte currentTile)
{
  switch (currentTile)
  {
    case 2:
      return -10;
      break;
    case 10:
      return 10;
      break;
    case 22:
      return 10;
      break;
    case 14:
      return -10;
      break;
  }
}

int offsetYAfterDoor(byte currentTile)
{
  switch (currentTile)
  {
    case 2:
      return -5;
      break;
    case 10:
      return -5;
      break;
    case 22:
      return 5;
      break;
    case 14:
      return 5;
      break;
  }
}

/////////////////  DRAW ROOM    ///////////////////
///////////////////////////////////////////////////
void drawNothing()
{
}

void drawFloor()
{
  for (byte y = 0; y < 5; y++)
  {
    for (byte x = 0; x < 5; x++)
    {
      sprites.drawPlusMask(48 - (12 * x) + (12 * y), currentRoomY + 27 + (6 * x) + (6 * y), floorTile_plus_mask, 0);
    }
  }
}

void drawWalls()
{
  for (byte x = 0; x < 6; x++)
  {
    sprites.drawSelfMasked( -2 + (10 * x), currentRoomY + 25 - (5 * x), wallParts, NORTH);
    sprites.drawSelfMasked(60 + (10 * x), currentRoomY + (5 * x), wallParts, EAST);
  }
}


///////////////// DRAW DOOR NORTH  ////////////////
///////////////////////////////////////////////////
void drawDoorLintelNorth()
{
  sprites.drawPlusMask(16, currentRoomY + 5, doorLintel_plus_mask, NORTH);
}

void drawDoorPostBigNorth()
{
  sprites.drawPlusMask(24, currentRoomY + 21, doorPostBig_plus_mask, NORTH);
}

void drawDoorPostSmallNorth()
{
  sprites.drawPlusMask(16, currentRoomY + 21, doorPostSmall_plus_mask, NORTH);
}

void drawDoorClossedNorth()
{
  sprites.drawPlusMask(24, currentRoomY + 14, doorClossed_plus_mask, NORTH);
}



/////////////////  DRAW DOOR EAST  ////////////////
///////////////////////////////////////////////////
void drawDoorLintelEast()
{
  sprites.drawPlusMask(80, currentRoomY + 5, doorLintel_plus_mask, EAST);
}

void drawDoorPostBigEast()
{
  sprites.drawPlusMask(80, currentRoomY + 21, doorPostBig_plus_mask, EAST);
}

void drawDoorPostSmallEast()
{
  sprites.drawPlusMask(95, currentRoomY + 21, doorPostSmall_plus_mask, EAST);
}

void drawDoorClossedEast()
{
  sprites.drawPlusMask(85, currentRoomY + 14, doorClossed_plus_mask, EAST);
}



/////////////////  DRAW DOOR SOUTH  ///////////////
///////////////////////////////////////////////////
void drawDoorLintelSouth()
{
  sprites.drawPlusMask(81, currentRoomY + 38, doorLintel_plus_mask, SOUTH);
}

void drawDoorPostBigSouth()
{
  sprites.drawPlusMask(89, currentRoomY + 54, doorPostBig_plus_mask, SOUTH);
}

void drawDoorPostSmallSouth()
{
  sprites.drawPlusMask(81, currentRoomY + 54, doorPostSmall_plus_mask, SOUTH);
}

void drawDoorClossedSouth()
{
  sprites.drawPlusMask(89 , currentRoomY + 47, doorClossed_plus_mask, SOUTH);
}



/////////////////   DRAW DOOR WEST  ///////////////
///////////////////////////////////////////////////
void drawDoorLintelWest()
{
  sprites.drawPlusMask(14, currentRoomY + 38, doorLintel_plus_mask, WEST);
}

void drawDoorPostBigWest()
{
  sprites.drawPlusMask(14, currentRoomY + 54, doorPostBig_plus_mask, WEST);
}

void drawDoorPostSmallWest()
{
  sprites.drawPlusMask(29, currentRoomY + 54, doorPostSmall_plus_mask, WEST);
}

void drawDoorClossedWest()
{
  sprites.drawPlusMask(19, currentRoomY + 47, doorClossed_plus_mask, WEST);
}



///////////////// DRAW ENEMIES //////////////
/////////////////////////////////////////////
void drawEnemyOne()
{
  sprites.drawPlusMask(enemy[0].x, enemy[0].y + currentRoomY, enemies_plus_mask, enemy[0].characteristics & 0b00000011 + (4 * ((enemy[0].characteristics & 0b11100000) >> 5)));
}

void drawEnemyTwo()
{
  sprites.drawPlusMask(enemy[1].x, enemy[1].y + currentRoomY, enemies_plus_mask, enemy[1].characteristics & 0b00000011 + (4 * ((enemy[1].characteristics & 0b11100000) >> 5)));
}



///////////////// DRAW ELEMENTS /////////////
/////////////////////////////////////////////
void drawObjectChangeable()
{
  if (arduboy.everyXFrames(8)) objectFrame++;
  if (objectFrame > 3) objectFrame = 0;
  sprites.drawPlusMask(enemy[2].x + 4, enemy[2].y + 9 + currentRoomY, elements_plus_mask, objectFrame + (4 * ((enemy[2].characteristics & 0b11100000) >> 5)));
}

void drawObjectFixedOne()
{
  sprites.drawPlusMask(enemy[3].x - 3, enemy[3].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[3].characteristics & 0b11100000) >> 5));
}

void drawObjectFixedTwo()
{
  sprites.drawPlusMask(enemy[4].x - 3, enemy[4].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[4].characteristics & 0b11100000) >> 5));
}

void drawObjectFixedThree()
{
  sprites.drawPlusMask(enemy[5].x - 3, enemy[5].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[5].characteristics & 0b11100000) >> 5));
}

void drawObjectFixedFour()
{
  sprites.drawPlusMask(enemy[6].x - 3, enemy[6].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[6].characteristics & 0b11100000) >> 5));
}

void drawObjectFixedFive()
{
  sprites.drawPlusMask(enemy[7].x - 3, enemy[7].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[7].characteristics & 0b11100000) >> 5));
}

void drawBulletPlayer()
{

}

void drawBulletEnemy()
{

}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM  updateElementsInRoom[] =
{
  drawEnemyOne,                     // 0
  drawEnemyTwo,                     // 1
  drawObjectChangeable,             // 2
  drawObjectFixedOne,               // 3
  drawObjectFixedTwo,               // 4
  drawObjectFixedThree,             // 5
  drawObjectFixedFour,              // 6
  drawObjectFixedFive,              // 7
  drawBulletEnemy,                  // 8

  drawPlayer,                       // 9
  drawBulletPlayer,                 // 10

  drawDoorLintelNorth,              // 11
  drawDoorPostBigNorth,             // 12
  drawDoorPostSmallNorth,           // 13
  drawDoorClossedNorth,             // 14

  drawDoorLintelEast,               // 15
  drawDoorPostBigEast,              // 16
  drawDoorPostSmallEast,            // 17
  drawDoorClossedEast,              // 18

  drawDoorLintelSouth,              // 19
  drawDoorPostBigSouth,             // 20
  drawDoorPostSmallSouth,           // 21
  drawDoorClossedSouth,             // 22

  drawDoorLintelWest,               // 23
  drawDoorPostBigWest,              // 24
  drawDoorPostSmallWest,            // 25
  drawDoorClossedWest,              // 26

  drawNothing,                      // 27
};


void updateRoom()
{
  drawWalls();
  drawFloor();
  byte itemsOrderCounter = 0;
  while ( itemsOrderCounter < SIZE_OF_ITEMSORDER)
  {
    ((FunctionPointer) pgm_read_word (&updateElementsInRoom[itemsOrder[itemsOrderCounter]]))();
    itemsOrderCounter++;
  }
}


void checkOrderOfObjects(byte roomNumber, byte currentLevel)
{
  // clear out the itemsOrder
  memset(itemsOrder, EMPTY_PLACE, SIZE_OF_ITEMSORDER);

  //draw door NORTH
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7))
  {
    itemsOrder[0] = NORTH_LINTEL;
    itemsOrder[1] = NORTH_BIG_POST;
    itemsOrder[3] = NORTH_SMALL_POST;
  }
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 3)) itemsOrder[4] = NORTH_DOOR_CLOSSED;


  //draw door EAST
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 6))
  {
    itemsOrder[5] = EAST_LINTEL;
    itemsOrder[6] = EAST_BIG_POST;
    itemsOrder[8] = EAST_SMALL_POST;
  }
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 2)) itemsOrder[9] = EAST_DOOR_CLOSSED;


  //draw door SOUTH
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 5))
  {
    itemsOrder[35] = SOUTH_LINTEL;
    itemsOrder[36] = SOUTH_BIG_POST;
    itemsOrder[38] = SOUTH_SMALL_POST;
  }
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 1)) itemsOrder[39] = SOUTH_DOOR_CLOSSED;


  //draw door WEST
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 4))
  {
    itemsOrder[40] = WEST_LINTEL;
    itemsOrder[41] = WEST_BIG_POST;
    itemsOrder[43] = WEST_SMALL_POST;
  }
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 0)) itemsOrder[44] = WEST_DOOR_CLOSSED;


  //******************************
  //determine what is on the tiles
  //******************************
  // check what tile the player is on (so that we can determine what order things need to be displayed)
  if (!bitRead(player.characteristics, 5) && !bitRead(player.characteristics, 6))
  {
    itemsOrder[tileFromXY(player.x, player.y - currentRoomY) + ITEMS_ORDER_TILES_START] = PLAYER_DROID;
    //Serial.println(tileFromXY(player.x, player.y - currentRoomY));
  }
  else
  {
    if (bitRead(player.characteristics, 5))
    {
      switch (player.characteristics & 0b00000011)
      {
        case NORTH:
          itemsOrder[2] = PLAYER_DROID;
          break;
        case EAST:
          itemsOrder[7] = PLAYER_DROID;
          break;
        case SOUTH:
          itemsOrder[37] = PLAYER_DROID;
          break;
        case WEST:
          itemsOrder[42] = PLAYER_DROID;
          break;
      }
    }
    if (bitRead(player.characteristics, 6))
    {
      switch (player.characteristics & 0b00000011)
      {
        case NORTH:
          itemsOrder[37] = PLAYER_DROID;
          break;
        case EAST:
          itemsOrder[42] = PLAYER_DROID;
          break;
        case SOUTH:
          itemsOrder[2] = PLAYER_DROID;
          break;
        case WEST:
          itemsOrder[7] = PLAYER_DROID;
          break;
      }
    }
  }

  // check what tile the 5 special floor tiles are on (so that we can determine what order things need to be displayed)
  for (byte i = 3; i < 8; i++)
  {
    if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - i))itemsOrder[tileFromXY(enemy[i].x, enemy[i].y) + ITEMS_ORDER_TILES_START] = i;
  }

  // check what tile the object are on (so that we can determine what order things need to be displayed)
  if (bitRead(stageRoom[currentRoom].enemiesActive, 5)) itemsOrder[tileFromXY(enemy[2].x, enemy[2].y) + ITEMS_ORDER_TILES_START] = 2;

  // check what tile the 2 enemies are on (so that we can determine what order things need to be displayed)
  for (byte i = 0; i < 2; i++)
  {
    if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - i)) itemsOrder[tileFromXY(enemy[i].x, enemy[i].y) + ITEMS_ORDER_TILES_START] = i;
  }


  for (byte i = 0; i < SIZE_OF_ITEMSORDER; i++)
  {
    //Serial.print(itemsOrder[i]);
    //Serial.print(" : ");
  }
  //Serial.println();
}

void updateHUDRoomNumber()
{
  if (arduboy.everyXFrames(20) && (player.life - 1 < 1)) player.characteristics ^= 0b10000000;
  //draw HUD mask
  for (byte y = 0; y < 8; y++) sprites.drawPlusMask(118, y * 8, hudMask_plus_mask, 0);

  //draw room number
  char buf[2];
  itoa(currentRoom, buf, 10);
  //itoa(arduboy.cpuLoad(), buf, 10);
  char charLen = strlen(buf);
  char pad = 2 - charLen;

  //draw 0 padding
  if (pad > 0) sprites.drawSelfMasked(121, 0, numbersThin, 0);

  //draw remaining digits
  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    sprites.drawSelfMasked(121 + (pad * 4) + (4 * i), 0, numbersThin, digit);
  }
  if (bitRead(player.characteristics, 7)) sprites.drawSelfMasked(120, 8, hudLife, player.life - 1);
}

void scoreDraw()
{
  char buf[7];
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    sprites.drawSelfMasked(43 + (6 * i), 54, numbersBig, 0);
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    sprites.drawSelfMasked(43 + (pad * 6) + (6 * i), 54, numbersBig, digit);

  }
}


#endif
