#ifndef ROOM_H
#define ROOM_H

#include "globals.h"
#include "levels.h"
#include "player.h"
#include "enemies.h"

#define MAX_AMOUNT_OF_ROOMS       32
#define SIZE_OF_ITEMSORDER        46

//define how collision works
#define DIFF(A, B) (((A) > (B)) ? ((A) - (B)) : ((B) - (A)))

byte doorsX[4] = {16, 80, 81, 14};
byte doorsY[4] = {5, 5, 38, 38};
byte frame = 0;

byte itemsOrder[32] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


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
    //                     |||||||└->  OBJECT 8 EXISTS (0 = false / 1 = true)
    //                     ||||||└-->  OBJECT 7 EXISTS (0 = false / 1 = true)
    //                     |||||└--->  OBJECT 6 EXISTS (0 = false / 1 = true)
    //                     ||||└---->  OBJECT 5 EXISTS (0 = false / 1 = true)
    //                     |||└----->  OBJECT 4 EXISTS (0 = false / 1 = true)
    //                     ||└------>  OBJECT 3 EXISTS (0 = false / 1 = true)
    //                     |└------->  OBJECT 2 EXISTS (0 = false / 1 = true)
    //                     └-------->  OBJECT 1 EXISTS (0 = false / 1 = true)
};

Room stageRoom[MAX_AMOUNT_OF_ROOMS];

void buildRooms(byte currentLevel)
{
  for (byte roomNumber = 0; roomNumber < MAX_AMOUNT_OF_ROOMS; roomNumber++)
  {
    //clear all info
    stageRoom[roomNumber].doorsClosedActive = 0;
    stageRoom[roomNumber].enemiesActive = 0;
    stageRoom[roomNumber].doorsClosedActive = pgm_read_byte(&levels[currentLevel - 1][1 + (13 * roomNumber)]);
    for (byte i = 0; i < 8; i++)
    {
      if ((pgm_read_byte(&levels[currentLevel - 1][6 + i + (13 * roomNumber)])) != 0)
      { //0b76543210
        bitSet (stageRoom[roomNumber].enemiesActive, 7 - i);    //0b12345678
      }
    }
  }
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
    if (bitRead (stageRoom[roomNumber].enemiesActive, 7 - i) == 1)
    {
      enemy[i].isVisible  = true;
      // set enemy on correct place 0 => 24)
      byte currentTile = (pgm_read_byte(&levels[currentLevel - 1][6 + i + (13 * roomNumber)])) >> 3;
      enemy[i].x = translateTileToX(currentTile);
      enemy[i].y = translateTileToY(currentTile);

      // first clear the characteristics
      enemy[i].characteristics = 0;
      // get kind of sprite (stored in level data) and put it into the 3 most left bits
      enemy[i].characteristics = ((pgm_read_byte(&levels[currentLevel - 1][6 + i + (13 * roomNumber)])) & 0b00000111) << 5;

      // we will always set the current direction to SOUTH (0b00000010)
      bitClear (enemy[i].characteristics, 0);
      bitSet (enemy[i].characteristics, 1);

      //set the enemy hurt/movable/pickup
    }
  }
}


byte goToRoom(byte roomNumber, byte currentLevel)
{
  // we now which door the player goes through by the direction the droid is facing
  byte door = player.characteristics & 0b00000011;
  return (pgm_read_byte(&levels[currentLevel - 1][1 + 1 + door + (13 * roomNumber)]) >> 2);
  //return 1;
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
    case 2: case 10:
      return -8;
      break;
    case 22: case 14:
      return -20;
      break;
  }
}

int offsetXAfterDoor(byte currentTile)
{
  switch (currentTile)
  {
    case 2:
      return -8;
      break;
    case 10:
      return 8;
      break;
    case 22:
      return 8;
      break;
    case 14:
      return -8;
      break;
  }
}

int offsetYAfterDoor(byte currentTile)
{
  switch (currentTile)
  {
    case 2:
      return -4;
      break;
    case 10:
      return -4;
      break;
    case 22:
      return 4;
      break;
    case 14:
      return 4;
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

///////////////// DRAW LINTEL  ////////////////////
///////////////////////////////////////////////////
void drawDoorLintelNorth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7))
  {
    sprites.drawPlusMask(16, currentRoomY + 5, doorLintel_plus_mask, NORTH);
  }
}

void drawDoorLintelEast()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 6))
  {
    sprites.drawPlusMask(80, currentRoomY + 5, doorLintel_plus_mask, EAST);
  }
}

void drawDoorLintelSouth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 5))
  {
    sprites.drawPlusMask(81, currentRoomY + 38, doorLintel_plus_mask, SOUTH);
  }
}

void drawDoorLintelWest()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 4))
  {
    sprites.drawPlusMask(14, currentRoomY + 38, doorLintel_plus_mask, WEST);
  }
}

///////////////// DRAW BIG POST  //////////////////
///////////////////////////////////////////////////
void drawDoorPostBigNorth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7))
  {
    sprites.drawPlusMask(24, currentRoomY + 21, doorPostBig_plus_mask, NORTH);
  }
}

void drawDoorPostBigEast()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 6))
  {
    sprites.drawPlusMask(80, currentRoomY + 21, doorPostBig_plus_mask, EAST);
  }
}

void drawDoorPostBigSouth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 5))
  {
    sprites.drawPlusMask(89, currentRoomY + 54, doorPostBig_plus_mask, SOUTH);
  }
}

void drawDoorPostBigWest()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 4))
  {
    sprites.drawPlusMask(14, currentRoomY + 54, doorPostBig_plus_mask, WEST);
  }
}


///////////////// DRAW SMALL POST  ////////////////
///////////////////////////////////////////////////
void drawDoorPostSmallNorth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7))
  {
    sprites.drawPlusMask(16, currentRoomY + 21, doorPostSmall_plus_mask, NORTH);
  }
}

void drawDoorPostSmallEast()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 6))
  {
    sprites.drawPlusMask(95, currentRoomY + 21, doorPostSmall_plus_mask, EAST);
  }
}

void drawDoorPostSmallSouth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 5))
  {
    sprites.drawPlusMask(81, currentRoomY + 54, doorPostSmall_plus_mask, SOUTH);
  }
}

void drawDoorPostSmallWest()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 4))
  {
    sprites.drawPlusMask(29, currentRoomY + 54, doorPostSmall_plus_mask, WEST);
  }
}


///////////////// DRAW DOOR CLOSSED  //////////////
///////////////////////////////////////////////////
void drawDoorClossedNorth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 3))
  {
    sprites.drawPlusMask(24, currentRoomY + 14, doorClossed_plus_mask, NORTH);
  }
}

void drawDoorClossedEast()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 2))
  {
    sprites.drawPlusMask(85, currentRoomY + 14, doorClossed_plus_mask, EAST);
  }
}

void drawDoorClossedSouth()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 1))
  {
    sprites.drawPlusMask(89 , currentRoomY + 47, doorClossed_plus_mask, SOUTH);
  }
}

void drawDoorClossedWest()
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 0))
  {
    sprites.drawPlusMask(19, currentRoomY + 47, doorClossed_plus_mask, WEST);
  }
}


///////////////// DRAW ENEMIES //////////////
/////////////////////////////////////////////
void drawEnemyOne()
{

  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - 0))
  {
    sprites.drawPlusMask(enemy[0].x, enemy[0].y + currentRoomY, enemies_plus_mask, enemy[0].characteristics & 0b00000011 + (4 * ((enemy[0].characteristics & 0b11100000) >> 5)));
  }
}

void drawEnemyTwo()
{

  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - 1))
  {
    sprites.drawPlusMask(enemy[1].x, enemy[1].y + currentRoomY, enemies_plus_mask, enemy[1].characteristics & 0b00000011 + (4 * ((enemy[1].characteristics & 0b11100000) >> 5)));
  }
}

///////////////// DRAW ELEMENTS /////////////
/////////////////////////////////////////////

void drawObjectChangeable()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 5))
  {
    if (arduboy.everyXFrames(8)) frame++;
    if (frame > 3) frame = 0;
    sprites.drawPlusMask(enemy[2].x + 4, enemy[2].y + 9 + currentRoomY, elements_plus_mask, frame + (4 * ((enemy[2].characteristics & 0b11100000) >> 5)));
  }
}

void drawObjectFixedOne()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - 3))
  {
    sprites.drawPlusMask(enemy[3].x - 3, enemy[3].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[3].characteristics & 0b11100000) >> 5));
  }
}

void drawObjectFixedTwo()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - 4))
  {
    sprites.drawPlusMask(enemy[4].x - 3, enemy[4].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[4].characteristics & 0b11100000) >> 5));
  }
}

void drawObjectFixedThree()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - 5))
  {
    sprites.drawPlusMask(enemy[5].x - 3, enemy[5].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[5].characteristics & 0b11100000) >> 5));
  }
}

void drawObjectFixedFour()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - 6))
  {
    sprites.drawPlusMask(enemy[6].x - 3, enemy[6].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[6].characteristics & 0b11100000) >> 5));
  }
}

void drawObjectFixedFive()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - 7))
  {
    sprites.drawPlusMask(enemy[7].x - 3, enemy[7].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[7].characteristics & 0b11100000) >> 5));
  }
}

void drawBulletPlayer()
{

}

void drawBulletEnemy()
{

}

/*
  void updateRoom()
  {
  byte amountOfItems = 0;
  drawWalls();
  drawFloor();
  drawDoorLintelNorth();
  drawDoorLintelEast();
  drawDoorPostBigNorth();
  drawDoorPostSmallNorth();
  drawDoorClossedNorth();
  drawDoorPostBigEast();
  drawDoorPostSmallEast();
  drawDoorClossedEast();
  while ( amountOfItems < SIZE_OF_ITEMSORDER)
  {
    switch (itemsOrder[amountOfItems])
    {
      case 0:
        break;
      case 1:
        drawPlayer();
        break;
      case 2:
        drawEnemyOne();
        break;
      case 3:
        drawEnemyTwo();
        break;
      case 4:
        drawObjectChangeable();
        break;
      case 5:
        drawObjectFixedOne();
        break;
      case 6:
        drawObjectFixedTwo();
        break;
      case 7:
        drawObjectFixedThree();
        break;
      case 8:
        drawObjectFixedFour();
        break;
      case 9:
        drawObjectFixedFive();
        break;
      case 10:
        drawBulletPlayer();
        break;
      case 11:
        drawBulletEnemy();
        break;
      default :
        break;
    }
    amountOfItems++;
  }
  drawDoorLintelSouth();
  drawDoorLintelWest();
  drawDoorPostBigSouth();
  drawDoorPostSmallSouth();
  drawDoorClossedSouth();
  drawDoorPostBigWest();
  drawDoorPostSmallWest();
  drawDoorClossedWest();
  }
*/

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM  updateElementsInRoom[] =
{
  drawNothing,                      // 0

  drawDoorLintelNorth,              // 1
  drawDoorPostBigNorth,             // 2
  drawPlayer,                       // 3
  drawDoorPostSmallNorth,           // 4
  drawDoorClossedNorth,             // 5

  drawDoorLintelEast,               // 6
  drawDoorPostBigEast,              // 7
  drawPlayer,                       // 8
  drawDoorPostSmallEast,            // 9
  drawDoorClossedEast,              // 10

  // between this starting at 0
  drawObjectChangeable,             // 11
  drawObjectFixedOne,               // 12
  drawObjectFixedTwo,               // 13
  drawObjectFixedThree,             // 14
  drawObjectFixedFour,              // 15
  drawObjectFixedFive,              // 16
  drawBulletPlayer,                 // 17
  drawBulletEnemy,                  // 18

  drawEnemyOne,                     // 19
  drawEnemyTwo,                     // 20

  drawPlayer,                       // 21

  // and this we need 25 places

  drawDoorLintelSouth,              // 22
  drawDoorPostBigSouth,             // 23
  drawPlayer,                       // 24
  drawDoorPostSmallSouth,           // 25
  drawDoorClossedSouth,             // 26

  drawDoorLintelWest,               // 27
  drawDoorPostBigWest,              // 28
  drawPlayer,                       // 29
  drawDoorPostSmallWest,            // 30
  drawDoorClossedWest,              // 31
};


void updateRoom()
{
  drawWalls();
  drawFloor();
  byte orderOfitems = 0;
  while ( orderOfitems < SIZE_OF_ITEMSORDER)
  {
    ((FunctionPointer) pgm_read_word (&updateElementsInRoom[itemsOrder[orderOfitems]]))(); // need to update a variable to draw the correct object //itemsOrder[orderOfitems]
    Serial.println(itemsOrder[orderOfitems]);
    orderOfitems++;
  }
}




void checkOrderOfObjects(byte roomNumber, byte currentLevel)
{
  // clear out the itemsOrder
  memset(itemsOrder, 0, SIZE_OF_ITEMSORDER);

  //draw door NORTH
  itemsOrder[0] = 1;
  itemsOrder[1] = 2;
  itemsOrder[2] = 0;
  itemsOrder[3] = 4;
  itemsOrder[4] = 5;

  //draw door EAST
  itemsOrder[5] = 6;
  itemsOrder[6] = 7;
  itemsOrder[7] = 0;
  itemsOrder[8] = 9;
  itemsOrder[9] = 10;

  //draw door SOUTH
  itemsOrder[36] = 22;
  itemsOrder[37] = 23;
  itemsOrder[38] = 0;
  itemsOrder[39] = 25;
  itemsOrder[40] = 26;

  //draw door WEST
  itemsOrder[41] = 27;
  itemsOrder[42] = 28;
  itemsOrder[43] = 0;
  itemsOrder[44] = 30;
  itemsOrder[45] = 31;

  /*
    // check what tile the 5 floor special tiles are on (so that we can determine what order things need to be displayed)
    for (byte i = 3; i < 8; i++)
    {
      itemsOrder[tileFromXY(enemy[i].x, enemy[i].y) + 12 ] = i + 2 + 7; //floor
    }


    // check what tile the 2 enemies and the object are on (so that we can determine what order things need to be displayed)
    for (byte i = 0; i < 3; i++)
    {
    itemsOrder[tileFromXY(enemy[i].x, enemy[i].y)] = i + 2; //enemy0
    }
  */

  // check what tile the player is on (so that we can determine what order things need to be displayed)
  if (!bitRead(player.characteristics, 5) && !bitRead(player.characteristics, 6))
  {
    itemsOrder[tileFromXY(player.x, player.y - currentRoomY) + 11] = 21;  //player
  }
  else
  {
    if (bitRead(player.characteristics, 5))
    {
      switch (player.characteristics & 0b00000011)
      {
        case NORTH:
          itemsOrder[2] = 21;
          break;
        case EAST:
          itemsOrder[7] = 21;
          break;
        case SOUTH:
          itemsOrder[38] = 21;
          break;
        case WEST:
          itemsOrder[43] = 21;
          break;
      }
    }
    if (bitRead(player.characteristics, 6))
    {
      switch (player.characteristics & 0b00000011)
      {
        case NORTH:
          itemsOrder[38] = 21;
          break;
        case EAST:
          itemsOrder[43] = 21;
          break;
        case SOUTH:
          itemsOrder[2] = 21;
          break;
        case WEST:
          itemsOrder[7] = 21;
          break;
      }
    }
  }
}

void updateHUDRoomNumber()
{
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
  sprites.drawSelfMasked(120, 8, hudLife, player.life - 1);
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
