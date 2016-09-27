#ifndef LEVELS_H
#define LEVELS_H

// DOORS         NORTH        EAST       SOUTH        WEST       ENEMY1      ENEMY2     OBJECT3     FLOOR1      FLOOR2      FLOOR3      FLOOR4      FLOOR5
//0b11001110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
//  ||||||||    ||||||||                                        ||||||||
//  ||||||||    ||||||||                                        |||||||└->  \
//  ||||||||    ||||||||                                        ||||||└-->   |  these 3 bits are used to determine kind of sprite used for the object
//  ||||||||    ||||||||                                        |||||└--->  /
//  ||||||||    ||||||||                                        ||||└---->  \
//  ||||||||    ||||||||                                        |||└----->   |
//  ||||||||    ||||||||                                        ||└------>   |  these 5 bits are used to determine on what floor tile the object is 
//  ||||||||    ||||||||                                        |└------->   |  if all 8 bits = 0 => no object 
//  ||||||||    ||||||||                                        └-------->  /
//  ||||||||    ||||||||
//  ||||||||    ||||||||
//  ||||||||    |||||||└->  \  these 2 bits are used to determine what door you'll go to
//  ||||||||    ||||||└-->  / 
//  ||||||||    |||||└--->  \
//  ||||||||    ||||└---->   |
//  ||||||||    |||└----->   | these 6 bits are used for the roomnumber you'll go to
//  ||||||||    ||└------>   |
//  ||||||||    |└------->   |
//  ||||||||    └-------->  /
//  ||||||||
//  ||||||||
//  |||||||└->  DOOR WEST  is closed (0 = false / 1 = true)
//  ||||||└-->  DOOR SOUTH is closed (0 = false / 1 = true)
//  |||||└--->  DOOR EAST  is closed (0 = false / 1 = true)
//  ||||└---->  DOOR NORTH is closed (0 = false / 1 = true)
//  |||└----->  DOOR WEST  exists    (0 = false / 1 = true)
//  ||└------>  DOOR SOUTH exists    (0 = false / 1 = true)
//  |└------->  DOOR EAST  exists    (0 = false / 1 = true)
//  └-------->  DOOR NORTH exists    (0 = false / 1 = true)

#define MAX_AMOUNT_OF_ROOMS         32
#define ROOMS_START_AT_BYTE         1
#define BYTES_USED_FOR_ROOMS        13


const unsigned char PROGMEM level01[]=
{
  4, // amount of rooms
  // DOORS         NORTH       EAST       SOUTH       WEST          ENEMY1      ENEMY2        OBJECT3       FLOOR1      FLOOR2      FLOOR3      FLOOR4      FLOOR5
  0b11111001,  0b00000000, 0b00001111, 0b00000100, 0b00000000,    0b00000000, 0b00000000,   0b00000000,   0b00000010, 0b00001010, 0b00010010, 0b00011010, 0b00100010,  //room00 
  0b11000000,  0b00000010, 0b00001011, 0b00000000, 0b00000000,    0b00100001, 0b11000001,   0b01100000,   0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room01
  0b10010000,  0b00001110, 0b00000000, 0b00000000, 0b00000101,    0b00000000, 0b00000000,   0b10100001,   0b01111011, 0b10000011, 0b10101011, 0b00000000, 0b00000000,  //room02
  0b00110000,  0b00000000, 0b00000000, 0b00001000, 0b00000001,    0b00000000, 0b00000000,   0b01100010,   0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room03
  };

  const unsigned char PROGMEM level02[]=
{
  4, // amount of rooms
  0b10001111, 0b10000000, 0b11000000, 0b00000000, 0b01000000,     0b00000000, 0b00000000,    0b00000000,  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room00
  255, 64,64,64,64, 64,64,64,64,64,64,64,64,  //room01
  255, 64,64,64,64, 64,64,64,64,64,64,64,64,  //room02
  255, 64,64,64,64, 64,64,64,64,64,64,64,64,  //room03
  };


const unsigned char *levels[] =
{
  level01, level02,
};


#endif
