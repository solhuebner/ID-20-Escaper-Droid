#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "inputs.h"

void stateMenuPlay()
{
  scorePlayer = 0;
  player.set();
  gameState = STATE_GAME_NEXT_LEVEL;
}

void stateGamePlaying()
{
  if (!bitRead(player.characteristics, 5))checkInputs();
  else if (arduboy.everyXFrames(2))
  {
    if (player.steps < 5)  walkThroughDoor();
    else
    {
      currentTile = goToTile(currentRoom, level);
      currentRoomY = setCurrentRoomY(currentTile);
      currentRoom = goToRoom(currentRoom, level);
      player.x = translateTileToX (currentTile) + offsetXAfterDoor(currentTile);
      player.y = translateTileToY (currentTile) + offsetYAfterDoor(currentTile) + currentRoomY ;
      player.steps = 0;
      enterRoom(currentRoom, level);
      bitClear (player.characteristics, 5);
      bitSet (player.characteristics, 6);
      gameState = STATE_GAME_NEXT_ROOM;
    }
  }
  
  checkOrderOfObjects(currentRoom, level);
  updateRoom();
  drawHUD();
  //Serial.println(tileFromXY(player.x, player.y - currentRoomY));
  
}


void stateGameNextRoom()
{
  if (arduboy.everyXFrames(2))
  {
    if (player.steps < 5)  walkThroughDoor();
    else
    {
      player.steps = 0;
      bitClear (player.characteristics, 6);
      gameState = STATE_GAME_PLAYING;
    }
  }
  checkOrderOfObjects(currentRoom, level);
  updateRoom();
  drawHUD();
}

void stateGameNextLevel()
{
  level++;
  currentRoom = 0;
  currentTile = TILE_GAME_STARTS_ON;
  currentRoomY = -14;
  player.x = translateTileToX (currentTile);
  player.y = translateTileToY (currentTile) + currentRoomY ;
  buildRooms(level);
  enterRoom(currentRoom, level);
  gameState = STATE_GAME_PLAYING;
}


void stateGamePause()
{
  sprites.drawSelfMasked(0, 0, pauseScreen, 0);
  drawNumbers(43,54,scorePlayer, BIG_FONT);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_GAME_PLAYING;
}

void stateGameOver()
{
  sprites.drawSelfMasked(0, 0, gameOverScreen, 0);
  drawNumbers(43,54,scorePlayer, BIG_FONT);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

#endif
