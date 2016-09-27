#ifndef MENU_H
#define MENU_H

#include "globals.h"
#include "room.h"

void drawTitleScreen()
{
  byte test;
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, titleScreen, i);
  sprites.drawSelfMasked(17, 56, mainMenus, gameState / 5);
}

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  if (globalCounter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  // show the titleScreen art
  drawTitleScreen();
  if (arduboy.everyXFrames(2))
  {
    selectorX++;
    selectorX2--;
  }
  if (selectorX > 34)selectorX = 17;
  if (selectorX2 < 18)selectorX2 = 35;
  sprites.drawPlusMask(selectorX + ((menuSelection - 2) * 24), 56, selector_plus_mask, 0);
  sprites.drawPlusMask(selectorX2 + ((menuSelection - 2) * 24), 56, selector_plus_mask, 0);
  if (arduboy.justPressed(RIGHT_BUTTON) && (menuSelection < 5)) menuSelection++;
  if (arduboy.justPressed(LEFT_BUTTON) && (menuSelection > 2)) menuSelection--;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = menuSelection;
}

void stateMenuHelp()
{
  for (byte i = 0; i < 2; i++) sprites.drawSelfMasked(32, 32 * i, qrcode, i);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuInfo()
{
  sprites.drawSelfMasked(16, 20, infoScreen, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  drawTitleScreen();
  if (arduboy.everyXFrames(2))
  {
    selectorX++;
    selectorX2--;
  }
  if (selectorX > 34)selectorX = 17;
  if (selectorX2 < 18)selectorX2 = 35;
  sprites.drawPlusMask(selectorX + (arduboy.audio.enabled() * 24) + 40, 56, selector_plus_mask, 0);
  sprites.drawPlusMask(selectorX2 + (arduboy.audio.enabled() * 24) + 40, 56, selector_plus_mask, 0);
  if (arduboy.justPressed(RIGHT_BUTTON)) arduboy.audio.on();
  if (arduboy.justPressed(LEFT_BUTTON)) arduboy.audio.off();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
}

#endif
