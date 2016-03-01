#ifndef COLLISION_H
#define COLLISION_H



boolean northBorder(int objectX, int objectY)
{
  // check the border of the room

  if (objectX + (2 * objectY) > 89 + (2 * currentRoomY)) return true; // if -30 => 23   if -22 => 39   if 0 => 83
  else return false;
}

boolean eastBorder(int objectX, int objectY)
{
  // check the border of the room

  if (objectX - (2 * objectY) < 15 - (2 * currentRoomY)) return true; // if -30 => 79   if -22 => 63   if 0 => 19
  else return false;
}

boolean southBorder(int objectX, int objectY)
{
  // check the border of the room

  if (objectX + (2 * objectY) < 183 + (2 * currentRoomY)) return true; // if -30 => 127   if -22 => 143   if 0 => 187
  else return false;
}

boolean westBorder(int objectX, int objectY)
{
  // check the border of the room

  if (objectX - (2 * objectY) > -81 - (2 * currentRoomY)) return true; // if -30 => -25   if -22 => -41   if 0 => -85
  else return false;
}


#endif
