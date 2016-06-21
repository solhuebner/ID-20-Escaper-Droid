#ifndef ENEMIES_H
#define ENEMIES_H

#include "globals.h"
#include "room.h"

byte objectFrame = 0;

struct Enemy
{
  public:
    int x, y;
    byte isVisible;
    byte characteristics = 0b00000000;   //this byte holds all the enemies characteristics
    //                       ||||||||
    //                       |||||||└->  \ this 2 bits are used for direction
    //                       ||||||└-->  / 00 = NORTH / 01 = EAST / 10 = SOUTH / 11 = WEST
    //                       |||||└--->  this enemy/object can hurt you         (0 = false / 1 = true)
    //                       ||||└---->  this object is movable by player       (0 = false / 1 = true)
    //                       |||└----->  this object can be picked up by player (0 = false / 1 = true)
    //                       ||└------>  \
    //                       |└------->   | these 3 bits are used to determine kind of sprite to use
    //                       └-------->  /

};

Enemy enemy[8];

#endif
