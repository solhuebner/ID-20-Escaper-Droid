#ifndef ROOM_H
#define ROOM_H

#include "globals.h"
#include "levels.h"
#include "player.h"
#include "enemies.h"

//define how collision works
#define DIFF(A, B) (((A) > (B)) ? ((A) - (B)) : ((B) - (A)))

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
  for (byte i = 0; i < 8; i++)
  {
    if ((pgm_read_byte(&levels[currentlevel - 1][6 + i + (13 * roomNumber)])) != 0)
    {                                                      //0b76543210
      bitSet (stageRoom[roomNumber].enemiesActive, 7 - i); //0b12345678
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

byte xFromTile(byte currentTile)
{

}

byte yFromTile(byte currentTile)
{

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

void enterRoom(byte roomNumber, byte currentlevel)
{
  for (byte i = 0; i < 8; i++)
  {
    //set all enemies at there position
    if (bitRead (stageRoom[roomNumber].enemiesActive, 7 - i) == 1)
    {
      //set enemy on correct place 0 => 24)
      byte currentTile = (pgm_read_byte(&levels[currentlevel - 1][6 + i + (13 * roomNumber)])) >> 3;
      enemy[i].x = translateTileToX(currentTile);
      enemy[i].y = translateTileToY(currentTile);



      //first clear the characteristics
      enemy[i].characteristics = 0;
      // get kind of sprite (stored in level data) and put it into the 3 most left bits
      enemy[i].characteristics = ((pgm_read_byte(&levels[currentlevel - 1][6 + i + (13 * roomNumber)])) & 0b00000111) << 5;

      // we will always set the current direction to SOUTH (0b00000010)
      bitClear (enemy[i].characteristics, 0);
      bitSet (enemy[i].characteristics, 1);

      //set the enemy hurt/movable/pickup
    }
  }
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


void drawDoorLintel(byte side)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7 - side) == 1)
  {
    sprites.drawPlusMask(doorsX[side], currentRoomY + doorsY[side], doorLintel_plus_mask, side);
  }
}

void drawDoorPostBig(byte side, byte vector)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7 - side) == 1)
  {
    sprites.drawPlusMask(doorsX[side] + 8 - (8 * vector), currentRoomY + 16 + doorsY[side], doorPostBig_plus_mask, side);
  }
}

void drawDoorPostSmall(byte side, byte vector)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 7 - side) == 1)
  {
    sprites.drawPlusMask(doorsX[side] + (15 * vector), currentRoomY + 16 + doorsY[side], doorPostSmall_plus_mask, side);
  }
}

void drawDoorClossed(byte side, byte vector)
{
  if (bitRead(stageRoom[currentRoom].doorsClosedActive, 3 - side) == 1)
  {
    sprites.drawPlusMask(doorsX[side] + 8 - (3 * vector), currentRoomY + 9 + doorsY[side], doorClossed_plus_mask, side);
  }
}


void drawEnemy(byte object)
{

  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - object) == 1)
  {
    sprites.drawPlusMask(enemy[object].x, enemy[object].y + currentRoomY, enemies_plus_mask, enemy[object].characteristics & 0b00000011 + (4 * ((enemy[object].characteristics & 0b11100000) >> 5)));
  }
}

void drawObjectChangeable()
{
  if (bitRead(stageRoom[currentRoom].enemiesActive, 5) == 1)
  {
    if (arduboy.everyXFrames(8)) frame++;
    if (frame > 3) frame = 0;
    sprites.drawPlusMask(enemy[2].x + 4, enemy[2].y + 9 + currentRoomY, elements_plus_mask, frame + (4 * ((enemy[2].characteristics & 0b11100000) >> 5)));
  }
}

void drawObjectFixed(byte object)
{

  if (bitRead(stageRoom[currentRoom].enemiesActive, 7 - object) == 1)
  {
    sprites.drawPlusMask(enemy[object].x - 3, enemy[object].y + currentRoomY + 9, floorTile_plus_mask, ((enemy[object].characteristics & 0b11100000) >> 5));
    Serial.print(enemy[object].x);
    Serial.print(" ");
    Serial.print(enemy[object].y);
    Serial.println();
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
      case 0:
        break;
      case 1:
        drawPlayer();
        break;
      case 2:
        drawEnemy(0);
        break;
      case 3:
        drawEnemy(1);
        break;
      case 4:
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
        //bulletPlayer();
        break;
      case 11:
        //bulletEnemy();
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
  // clear out the itemsOrder
  memset(itemsOrder, 0, sizeof(itemsOrder));

  // check what tile the 5 floor special tiles are on (so that we can determine what order things need to be displayed)
  for (byte i = 3; i < 8; i++)
  {
    itemsOrder[tileFromXY(enemy[i].x, enemy[i].y)] = i + 2; //floor
  }

  // check what tile the player is on (so that we can determine what order things need to be displayed)
  itemsOrder[tileFromXY(player.x, player.y - currentRoomY)] = 1;  //player

  // check what tile the 2 enemies and the object are on (so that we can determine what order things need to be displayed)
  for (byte i = 0; i < 3; i++)
  {
    itemsOrder[tileFromXY(enemy[i].x, enemy[i].y)] = i + 2; //enemy0
  }


  /*
    for (byte i = 0; i < sizeof(itemsOrder); i++)
    {
    Serial.print(itemsOrder[i]);
    Serial.print(" , ");
    }
    Serial.println();
  */
  //Serial.println(pgm_read_byte(&levels[currentlevel - 1][6 + 1 ]),BIN);
}

void updateHUDRoomNumber()
{
  //draw HUD mask
  for (byte y = 0; y < 8; y++) sprites.drawBitmap(118, y * 8, HUD_plus_mask, NULL, 2, 8, SPRITE_PLUS_MASK);

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
  sprites.drawSelfMasked(120, 8, hudLife, player.life -1);
}


#endif
