#ifndef MENU_H
#define MENU_H

#include "globals.h"
#include "room.h"

void stateMenuIntro()
{
  arduboy.drawBitmap(0, 8, TEAMarg, 128, 48, WHITE);
  counter++;
  if (counter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  // show the titleScreen art
  arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
  arduboy.drawBitmap(17, 56, mainMenu, 93, 8, WHITE);
  if (arduboy.everyXFrames(2))
  {
    selectorX++;
    selectorX2--;
  }
  if (selectorX > 34)selectorX = 17;
  if (selectorX2 < 18)selectorX2 = 35;
  sprites.drawPlusMask(selectorX + ((menuSelection - 2) * 24), 56, selector_plus_mask, 0);
  sprites.drawPlusMask(selectorX2 + ((menuSelection - 2) * 24), 56, selector_plus_mask, 0);
  if (buttons.justPressed(RIGHT_BUTTON) && (menuSelection < 5)) menuSelection++;
  if (buttons.justPressed(LEFT_BUTTON) && (menuSelection > 2)) menuSelection--;
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = menuSelection;
}

void stateMenuHelp()
{
  arduboy.drawBitmap(32, 0, qrcode, 64, 64, WHITE);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuInfo()
{
  arduboy.drawBitmap(16, 20, info_bitmap, 96, 24, WHITE);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  arduboy.drawBitmap(0, 0, titleScreen, 128, 64, WHITE);
  arduboy.drawBitmap(17, 56, soundMenu, 93, 8, WHITE);
  if (arduboy.everyXFrames(2))
  {
    selectorX++;
    selectorX2--;
  }
  if (selectorX > 34)selectorX = 17;
  if (selectorX2 < 18)selectorX2 = 35;
  sprites.drawPlusMask(selectorX + (soundYesNo * 24) + 40, 56, selector_plus_mask, 0);
  sprites.drawPlusMask(selectorX2 + (soundYesNo * 24) + 40, 56, selector_plus_mask, 0);
  if (buttons.justPressed(RIGHT_BUTTON)) soundYesNo = true;
  if (buttons.justPressed(LEFT_BUTTON)) soundYesNo = false;
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.save_on_off();
    gameState = STATE_MENU_MAIN;
  }
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
}

void stateMenuPlay()
{
  scorePlayer = 1234567;
  currentRoom = 0;
  currentRoomY = -14;
  level = 1;
  buildRoom(currentRoom, level);
  enterRoom(currentRoom, level);
  player.reset();
  gameState = STATE_GAME_PLAYING;
}

#endif
