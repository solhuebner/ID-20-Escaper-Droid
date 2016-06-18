#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "inputs.h"

void stateMenuPlay()
{
  scorePlayer = 1234567;
  currentRoom = 0;
  currentRoomY = -14;
  buildRoom(currentRoom, level);
  enterRoom(currentRoom, level);
  player.set();
  player.reset();
  gameState = STATE_GAME_PLAYING;
}

void stateGamePlaying()
{
  if (!bitRead(player.characteristics, 5))checkInputs();
  else walkThroughDoor();
  checkOrderOfObjects(currentRoom, level);
  updateRoom();
  updateHUDRoomNumber();
  
  Serial.println(tileFromXY(player.x, player.y - currentRoomY));
}
void stateGamePause()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, pauseScreen, i);
  scoreDraw();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_GAME_PLAYING;
}
void stateGameOver()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, gameOverScreen, i);
  scoreDraw();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

#endif
