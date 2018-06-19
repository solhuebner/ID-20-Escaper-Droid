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
#define PICKUP_BATTERY            2     // 1 extra life
#define PICKUP_BULLET             3     // 1 shot
#define PICKUP_CHIP               4     // extra points
#define TELEPORT                  5     // TELEPORT

#define FLOOR_TILE                0
#define FLOOR_BOX                 1
#define FLOOR_SPIKE               2
#define FLOOR_PIRAMIDE            3
#define FLOOR_PIT                 4

#define SCORE_BLACK_CARD          100
#define SCORE_WHITE_CARD          10
#define SCORE_LIFE                20
#define SCORE_BULLET              30
#define SCORE_CHIP                200


byte objectFrame = 0;

struct Element
{
  public:
    int x, y;
    byte characteristics = 0b00000000;   //this byte holds all the enemies characteristics
    //                       ||||||||
    //                       |||||||└->  0 \
    //                       ||||||└-->  1  | these 3 bits are used to determine kind of sprite to use 
    //                       |||||└--->  2 /
    //                       ||||└---->  3 \  these 2 bits are used for direction
    //                       |||└----->  4 /  00 = NORTH / 01 = EAST / 10 = SOUTH / 11 = WEST
    //                       ||└------>  5 this enemy/object can hurt you         (0 = false / 1 = true)
    //                       |└------->  6 this object is movable by player       (0 = false / 1 = true)
    //                       └-------->  7 this object can be picked up by player (0 = false / 1 = true)
};

Element elements[8];

#endif
