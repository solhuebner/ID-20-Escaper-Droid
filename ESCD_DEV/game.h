#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "inputs.h"

extern byte level;
extern byte displayLevel;

void scoreDraw()
{
  char buf[7];
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    sprites.drawSelfMasked(43 + (6 * i), 54, numbersBig, 0);
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    sprites.drawSelfMasked(43 + (pad * 6) + (6 * i), 54, numbersBig, digit);

  }
}

void stateGamePlaying()
{
  if (arduboy.everyXFrames(2))checkInputs();
  checkOrderOfObjects(currentRoom, level);
  updateRoom();
  updateHUDRoomNumber();
  //Serial.println(tileFromXY(player.x, player.y - currentRoomY));
}
void stateGamePause()
{
  arduboy.drawBitmap(0, 0, pauseScreen, 128, 64, WHITE);
  scoreDraw();
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_GAME_PLAYING;
}
void stateGameOver()
{
  arduboy.drawBitmap(0, 0, gameOverScreen, 128, 64, WHITE);
  scoreDraw();
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

#endif
