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

const unsigned char PROGMEM level01[]=
{
  4, // amount of rooms
  // DOORS         NORTH       EAST       SOUTH       WEST          ENEMY1      ENEMY2        OBJECT3       FLOOR1      FLOOR2      FLOOR3      FLOOR4      FLOOR5
  0b11111101,  0b00000000, 0b00000000, 0b00000100, 0b00000000,    0b00100001, 0b11000001,   0b01100010,   0b00000010, 0b00101011, 0b01010011, 0b01111011, 0b10100100,  //room00 
  0b10000000,  0b00000010, 0b00000000, 0b00000000, 0b00000000,    0b00000000, 0b00000000,   0b00000000,   0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room01
  0b01001111,  0b10000000, 0b11000000, 0b00000000, 0b01000000,    0b00000000, 0b00000000,   0b00000000,   0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room02
  0b10001111,  0b10000000, 0b11000000, 0b00000000, 0b01000000,    0b00000000, 0b00000000,   0b00000000,   0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room03
  };

  const unsigned char PROGMEM level02[]=
{
  4, // amount of rooms
  0b10001111, 0b10000000, 0b11000000, 0b00000000, 0b01000000,  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,//room00
  255, 64,64,64,64, 64,64,64,64,64,64,64,64,  //room01
  255, 64,64,64,64, 64,64,64,64,64,64,64,64,  //room02
  255, 64,64,64,64, 64,64,64,64,64,64,64,64,  //room03
  };


const unsigned char *levels[] =
{
  level01, level02,
};


#endif
