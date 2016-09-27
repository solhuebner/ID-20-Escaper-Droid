#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "globals.h"
#include "room.h"

#define ENEMY_ONE                 0
#define ENEMY_TWO                 1
#define OBJECT_THREE              2
#define FLOOR_ONE                 3
#define FLOOR_TWO                 4
#define FLOOR_THREE               5
#define FLOOR_FOUR                6
#define FLOOR_FIVE                7
#define ENEMY_BULLET              8

#define ENEMY_MOVING              0
#define ENEMY_SHOTING             1

#define PICKUP_BLACK_CARD         0     // opens level door
#define PICKUP_WHITE_CARD         1     // opens normal door
#define PICKUP_BATTERY            3     // 1 extra life
#define PICKUP_BULLET             4     // 1 shot
#define PICKUP_CHIP               5     // extra points

#define FLOOR_TILE                0
#define FLOOR_BOX                 1
#define FLOOR_SPIKE               2
#define FLOOR_PIRAMIDE            3
#define FLOOR_PIT                 4


byte objectFrame = 0;

struct Element
{
  public:
    int x, y;
    byte characteristics = 0b00000000;   //this byte holds all the enemies characteristics
    //                       ||||||||
    //                       |||||||└->  \  these 2 bits are used for direction
    //                       ||||||└-->  /  00 = NORTH / 01 = EAST / 10 = SOUTH / 11 = WEST
    //                       |||||└--->     this enemy/object can hurt you         (0 = false / 1 = true)
    //                       ||||└---->     this object is movable by player       (0 = false / 1 = true)
    //                       |||└----->     this object can be picked up by player (0 = false / 1 = true)
    //                       ||└------>  \
    //                       |└------->   | these 3 bits are used to determine kind of sprite to use
    //                       └-------->  /
};

Element elements[8];

#endif
