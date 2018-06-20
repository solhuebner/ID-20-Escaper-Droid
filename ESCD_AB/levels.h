#ifndef LEVELS_H
#define LEVELS_H

#define MAX_AMOUNT_OF_ROOMS                       32
#define MAX_AMOUNT_OF_INFLUENCING_OBJECTS         16
#define MAX_AMOUNT_OF_TRANSPORTERS                16
#define AMOUNT_OF_ROOMS_AT_BYTE                   0
#define ROOMS_DATA_START_AT_BYTE                  3
#define DOORS_DATA_START_AT_BYTE                  ROOMS_DATA_START_AT_BYTE + 1
#define ELEMENTS_DATA_START_AT_BYTE               ROOMS_DATA_START_AT_BYTE + 5
#define BYTES_USED_FOR_EVERY_ROOM                 13

// DOORS         NORTH        EAST       SOUTH        WEST       ENEMY1      ENEMY2     OBJECT3     FLOOR1      FLOOR2      FLOOR3      FLOOR4      FLOOR5
//0b11001110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
//  ||||||||    ||||||||                                        ||||||||
//  ||||||||    ||||||||                                        |||||||└->  \
//  ||||||||    ||||||||                                        ||||||└-->   |  these 3 bits are used to determine kind of sprite used for the object
//  ||||||||    ||||||||                                        |||||└--->  /
//  ||||||||    ||||||||                                        ||||└---->  \
//  ||||||||    ||||||||                                        |||└----->   |
//  ||||||||    ||||||||                                        ||└------>   |  these 5 bits are used to determine on what floor tile the object is
//  ||||||||    ||||||||                                        |└------->   |  
//  ||||||||    ||||||||                                        └-------->  /   if all 8 bits == 0 => no object
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
//
//
//
// ROOM+DIR       TILE
//0b00000001, 0b00000001,
//  ||||||||    ||||||||
//  ||||||||    |||||||└->  \
//  ||||||||    ||||||└-->   |
//  ||||||||    |||||└--->   |  these 5 bits are used to determine on what floor tile the object is
//  ||||||||    ||||└---->   |
//  ||||||||    |||└----->  /
//  ||||||||    ||└------>  \
//  ||||||||    |└------->   |  these 3 bits
//  ||||||||    └-------->  /
//  ||||||||
//  ||||||||
//  |||||||└->  \  these 2 bits are used for direction
//  ||||||└-->  /  00 = NORTH / 01 = EAST / 10 = SOUTH / 11 = WEST
//  |||||└--->  \
//  ||||└---->   |
//  |||└----->   | these 6 bits are used for the roomnumber you'll go to
//  ||└------>   |
//  |└------->   |
//  └-------->  /
//
//
//
//    ROOM      ELEMENT
//0b00000001, 0b00000001,
//  ||||||||    ||||||||
//  ||||||||    |||||||└->  7 => 0 FLOOR  5 INFLUENCED (0 = false / 1 = true)
//  ||||||||    ||||||└-->  6 => 1 FLOOR  4 INFLUENCED (0 = false / 1 = true)
//  ||||||||    |||||└--->  5 => 2 FLOOR  3 INFLUENCED (0 = false / 1 = true)
//  ||||||||    ||||└---->  4 => 3 FLOOR  2 INFLUENCED (0 = false / 1 = true)
//  ||||||||    |||└----->  3 => 4 FLOOR  1 INFLUENCED (0 = false / 1 = true)
//  ||||||||    ||└------>  2 => 5 OBJECT 3 INFLUENCED (0 = false / 1 = true)
//  ||||||||    |└------->  1 => 6 ENEMY  2 INFLUENCED (0 = false / 1 = true)
//  ||||||||    └-------->  0 => 7 ENEMY  1 INFLUENCED (0 = false / 1 = true)
//  ||||||||
//  ||||||||
//  |||||||└->  \
//  ||||||└-->   |
//  |||||└--->   |  these 6 bits are used for the roomnumber in which the element is influenced
//  ||||└---->   |
//  |||└----->   | 
//  ||└------>  /
//  |└------->
//  └-------->


const unsigned char PROGMEM level01[] =
{
  4, // amount of rooms
  2, // amount of transporters
  3, // amount of influencing objects
  // DOORS         NORTH       EAST       SOUTH       WEST          ENEMY1      ENEMY2        OBJECT3       FLOOR1      FLOOR2      FLOOR3      FLOOR4      FLOOR5
  0b11111001,  0b00000000, 0b00001111, 0b00000100, 0b00000000,    0b00000000, 0b00000000,   0b00000000,   0b00000010, 0b00001010, 0b00010010, 0b00011010, 0b00100010,  //room00
  0b11000000,  0b00000010, 0b00001011, 0b00000000, 0b00000000,    0b00100000, 0b11000001,   0b01100011,   0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room01
  0b10010000,  0b00001110, 0b00000000, 0b00000000, 0b00000101,    0b00000000, 0b00000000,   0b10100001,   0b01111011, 0b10000011, 0b10101011, 0b00000000, 0b00000000,  //room02
  0b00110000,  0b00000000, 0b00000000, 0b00001000, 0b00000001,    0b00000000, 0b00000000,   0b01100101,   0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room03

  // transporters data, the order of the data is by ascending numbers
  // ROOM+DIR     TILE
  0b00000001,  0b00000001,
  0b00000011,  0b00000011,

  // data about the elements that get influenced
  // ROOM         ELEMENT
  0b00000001,  0b00000001,
  0b00000011,  0b00000011,
  0b00000100,  0b00011111,

};

const unsigned char PROGMEM level02[] =
{
  4, // amount of rooms
  1, // amount of transporters (the actual amount is this number double)
  3, // amount of influencing objects
  0b10001111, 0b10000000, 0b11000000, 0b00000000, 0b01000000,     0b00000000, 0b00000000,    0b00000000,  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,  //room00
  255, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, //room01
  255, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, //room02
  255, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, //room03

  // transporters data, the order of the data is by ascending numbers
  // Room going to    tile going to
  0b00000001,         0b00000001,
  0b00000011,         0b00000011,

  // data about the elements that get influenced
  // ROOM         ELEMENT
  0b00000001,  0b00000001,
  0b00000011,  0b00000011,
  0b00000100,  0b00011111,
};


const unsigned char *levels[] =
{
  level01, level02,
};


#endif
