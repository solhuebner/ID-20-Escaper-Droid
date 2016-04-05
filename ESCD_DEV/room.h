#ifndef ROOM_H
#define ROOM_H

#include "globals.h"
#include "levels.h"
#include "player.h"
#include "enemies.h"

//define room directions
#define NORTH                    0
#define EAST                     1
#define SOUTH                    2
#define WEST                     3

#define NORTH_SOUTH              0
#define EAST_WEST                1

//define how collision works
#define DIFF(A, B) (((A) > (B)) ? ((A) - (B)) : ((B) - (A)))

extern Arduboy arduboy;
extern byte currentRoom;
extern int currentRoomY;
extern byte tile;

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
    //                         |||||||└->  DOOR WEST  IS CLOSED (0 = false / 1 = true)
    //                         ||||||└-->  DOOR SOUTH IS CLOSED (0 = false / 1 = true)
    //                         |||||└--->  DOOR EAST  IS CLOSED (0 = false / 1 = true)
    //                         ||||└---->  DOOR NORTH IS CLOSED (0 = false / 1 = true)
    //                         |||└----->  DOOR WEST  EXISTS    (0 = false / 1 = true)
    //                         ||└------>  DOOR SOUTH EXISTS    (0 = false / 1 = true)
    //                         |└------->  DOOR EAST  EXISTS    (0 = false / 1 = true)
    //                         └-------->  DOOR NORTH EXISTS    (0 = false / 1 = true)

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

Room stageRoom[32];

void buildRoom(byte roomNumber, byte currentlevel)
{
  stageRoom[roomNumber].doorsClosedActive = pgm_read_byte(&levels[currentlevel - 1][1 + (13 * roomNumber)]);
  for (byte x = 0; x < 8; x++)
  {
    if ((pgm_read_byte(&levels[currentlevel - 1][6 + x + (13 * roomNumber)])) != 0)
    {
      bitSet (stageRoom[roomNumber].enemiesActive, 7 - x);
    }
  }
}



uint8_t tileFromXY(uint8_t x, uint8_t y) {
  uint16_t x45 = x * 170;
  uint16_t y45 = y * 341;
  x = (((y45 - x45) >> 8) + 18);
  y = (((y45 + x45) >> 8) - 49);
  return (y >> 4) * 5 + (x >> 4);
}

bool isoCollide(uint8_t ax, uint8_t ay, uint8_t bx, uint8_t by, uint8_t max) {
  return (DIFF(ax, bx) + DIFF(ay, by)) < max;
}


int translateTileToX (byte currentTile)
{
  //  3 15 27 39 51
  // 15 27 39 51 63
  // 27 39 51 63 75
  // 39 51 63 75 87
  // 51 63 75 87 99

  //  4  3  2  1  0
  //  9  8  7  6  5
  // 14 13 12 11 10
  // 19 18 17 16 15
  // 24 23 22 21 20

  return ((((((currentTile / 5) * 6) + 4) - currentTile) * 12) + 3);
  //return (((12*currentTile)/5)+51);
}

int translateTileToY (byte currentTile)
{
  // 42 36 30 24 18
  // 48 42 36 30 24
  // 54 48 42 36 30
  // 60 54 48 42 36
  // 66 60 54 48 42

  //  4  3  2  1  0
  //  9  8  7  6  5
  // 14 13 12 11 10
  // 19 18 17 16 15
  // 24 23 22 21 20
  return (18 + (currentTile * 6) - ((currentTile / 5) * 24));
  //return (6*currentTile)/5 + 18;
}

void enterRoom(byte roomNumber, byte currentlevel)
{
  for (byte x = 0; x < 8; x++)
  {
    //set all enemies at there position
    if (bitRead (stageRoom[roomNumber].enemiesActive, 7 - x) == 1)
    {
      //set enemy on correct place 0 => 24)
      byte currentTile = (pgm_read_byte(&levels[currentlevel - 1][6 + x + (13 * roomNumber)])) >> 3;
      enemy[x].x = translateTileToX(currentTile);
      enemy[x].y = translateTileToY(currentTile);

      //set enemy sprite type
      enemy[x].characteristics = 0;
      // get kind of sprite (stored in level data) and put it into the 3 mosft left bits
      byte currentSprite = ((pgm_read_byte(&levels[currentlevel - 1][6 + x + (13 * roomNumber)])) & 0b00000111) << 5;
      // we will always set the current direction to SOUTH (0b00000010)
      bitClear (enemy[x].characteristics,0);
      bitSet (enemy[x].characteristics,1);
    }
  }
}


void drawFloor()
{
  for (byte y = 0; y < 5; y++)
  {
    for (byte x = 0; x < 5; x++)
    {
      sprites.drawBitmap( 48 - (12 * x) + (12 * y), currentRoomY + 32 + (6 * x) + (6 * y), floorTile, NULL, 22, 13, SPRITE_IS_MASK);
    }
  }
}


void drawWalls()
{
  for (byte x = 0; x < 6; x++)
  {
    sprites.drawBitmap( -2 + (10 * x), currentRoomY + 25 - (5 * x), wallPartNorth, NULL, 10, 36, SPRITE_IS_MASK);
    sprites.drawBitmap(60 + (10 * x), currentRoomY + (5 * x), wallPartEast, NULL, 10, 36, SPRITE_IS_MASK);
  }
}


void drawDoorLintel(byte side)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7 - side) == 1)
  {
    sprites.drawBitmap( doorsX[side], currentRoomY + doorsY[side], doorLintelPlusMask[side], NULL, 23, 16, SPRITE_PLUS_MASK);
  }
}

void drawDoorPostBig(byte side, byte vector)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7 - side) == 1)
  {
    sprites.drawBitmap(doorsX[side] + 8 - (8 * vector), currentRoomY + 16 + doorsY[side], doorPostBigPlusMask[side], NULL, 15, 29, SPRITE_PLUS_MASK);
  }
}

void drawDoorPostSmall(byte side, byte vector)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7 - side) == 1)
  {
    sprites.drawBitmap(doorsX[side] + (15 * vector), currentRoomY + 16 + doorsY[side], doorPostSmallPlusMask[side], NULL, 8, 30, SPRITE_PLUS_MASK);
  }
}

void drawDoorClossed(byte side, byte vector)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 3 - side) == 1)
  {
    sprites.drawBitmap(doorsX[side] + 8 - (3 * vector), currentRoomY + 9 + doorsY[side], doorClossedPlusMask[side], NULL, 10, 28, SPRITE_PLUS_MASK);
  }
}


void drawEnemy(byte object)
{
  
  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - object) == 1)
  {
    sprites.drawBitmap( enemy[object].x, enemy[object].y + currentRoomY, enemiesPlusMask[(enemy[object].characteristics & 0b00000011)], NULL, 16, 24, SPRITE_PLUS_MASK); //+(4*((enemy[object].characteristics & 0b11100000)>>5))
  }
}

void drawObjectChangeable()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 5) == 1)
  if (arduboy.everyXFrames(8))
  {
    frame++;
  }
  if (frame > 3) frame = 0;
  {
    sprites.drawBitmap( enemy[2].x-4, enemy[2].y+8 + currentRoomY, objectChangablePlusMask[frame+(4*((enemy[2].characteristics & 0b11100000)>>5))], NULL, 24, 16, SPRITE_PLUS_MASK);
  }
}

void drawObjectFixed(byte object)
{
  
  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - object) == 1)
  {
    sprites.drawBitmap( enemy[object].x, enemy[object].y + currentRoomY, enemiesPlusMask[0], NULL, 16, 24, SPRITE_PLUS_MASK);
  }
}


void updateRoom()
{
  byte amountOfItems = 0;
  drawWalls();
  drawFloor();
  drawDoorLintel(NORTH);
  drawDoorLintel(EAST);
  drawDoorPostBig(NORTH, NORTH_SOUTH);
  drawDoorPostSmall(NORTH, NORTH_SOUTH);
  drawDoorClossed(NORTH, NORTH_SOUTH);
  drawDoorPostBig(EAST, EAST_WEST);
  drawDoorPostSmall(EAST, EAST_WEST);
  drawDoorClossed(EAST, EAST_WEST);
  while ( amountOfItems < sizeof(itemsOrder))
  {
    switch (itemsOrder[amountOfItems])
    {
      case 1:
        //drawPlayer();
        break;
      case 2:
        drawEnemy(0);
        break;
      case 3:
        drawEnemy(1);
        break;
      case 4:
        //drawEnemy(2);
        drawObjectChangeable();
        break;
      case 5:
        drawObjectFixed(3);
        break;
      case 6:
        drawObjectFixed(4);
        break;
      case 7:
        drawObjectFixed(5);
        break;
      case 8:
        drawObjectFixed(6);
        break;
      case 9:
        drawObjectFixed(7);
        break;
      case 10:
        drawPlayer();
        break;
      default :
        break;
    }
    amountOfItems++;
  }
  drawDoorLintel(SOUTH);
  drawDoorLintel(WEST);
  drawDoorPostBig(SOUTH, NORTH_SOUTH);
  drawDoorPostSmall(SOUTH, NORTH_SOUTH);
  drawDoorClossed(SOUTH, NORTH_SOUTH);
  drawDoorPostBig(WEST, EAST_WEST);
  drawDoorPostSmall(WEST, EAST_WEST);
  drawDoorClossed(WEST, EAST_WEST);
}

void checkOrderOfObjects(byte roomNumber, byte currentlevel)
{
  memset(itemsOrder, 0, sizeof(itemsOrder));
  // check what tile the player is on (so that we can determine what order things need to be displayed)
  itemsOrder[tileFromXY(player.x, player.y - currentRoomY)] = 10;  //player

  // check what tile the 2 enemies and the object are on (so that we can determine what order things need to be displayed)
  for (byte x = 0; x < 3; x++)
  {
    itemsOrder[tileFromXY(enemy[x].x, enemy[x].y)] = x+2;    //enemy0
  }

  // check what tile the 5 floor special tiles are on (so that we can determine what order things need to be displayed)
  for (byte x = 3; x < 8; x++)
  {
    byte order = (pgm_read_byte(&levels[currentlevel - 1][6 + x + (13 * roomNumber)])) >> 3;
    itemsOrder[order] = x+2;
  }
}

void updateHUD()
{
  for (byte y = 0; y < 8; y++) sprites.drawBitmap(118, y * 8, HUD_plus_mask, NULL, 2, 8, SPRITE_PLUS_MASK);

  //draw room number
  char buf[2];
  //itoa(currentRoom, buf, 10);
  itoa(arduboy.cpuLoad(), buf, 10);
  char charLen = strlen(buf);
  char pad = 2 - charLen;

  //draw 0 padding
  if (pad > 0) sprites.drawBitmap(121, 0, number0Small, NULL, 3, 7, SPRITE_IS_MASK);

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
    sprites.drawBitmap(121 + (pad * 4) + (4 * i), 0, numbersSmall[digit], NULL, 3, 7, SPRITE_IS_MASK);
  }
}

#endif
