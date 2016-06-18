#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "inputs.h"

void stateMenuPlay()
{
  buildRooms(level);
  enterRoom(currentRoom, level);
  scorePlayer = 1234567;
  player.set();
  gameState = STATE_GAME_PLAYING;
}

void stateGamePlaying()
{
  if (!bitRead(player.characteristics, 5))checkInputs();
  else if (arduboy.everyXFrames(10))
  {
    if (player.steps < 4)  walkThroughDoor();
    else
    {
      currentRoom = goToRoom(currentRoom, level);
      player.steps = 0;
      gameState = STATE_GAME_NEXT_ROOM;
    }
  }
  checkOrderOfObjects(currentRoom, level);
  updateRoom();
  updateHUDRoomNumber();

  Serial.println(tileFromXY(player.x, player.y - currentRoomY));
}


void stateGameNextRoom()
{
  bitClear (player.characteristics, 5);
  enterRoom(currentRoom, level);
  gameState = STATE_GAME_PLAYING;
}

void stateGameNextLevel()
{
  level++;
  currentRoom = 0;
  currentRoomY = -14;
  buildRooms(level);
  enterRoom(currentRoom, level);
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
