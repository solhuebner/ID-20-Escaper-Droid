/*
 Escaper Droid: http://www.team-arg.org/escd-manual.html

 Arduboy version 0.4d:  http://www.team-arg.org/escd-downloads.html

 MADE by TEAM a.r.g. : http://www.team-arg.org/About.html

 2016 - JO3RI

 Game License: MIT : https://opensource.org/licenses/MIT

 */

//determine the game
#define GAME_ID 20

#include <SPI.h>
#include <EEPROM.h>
#include "Arglib.h"
#include "menu_bitmaps.h"
#include "room.h"
#include "inputs.h"
#include "numbers_bitmaps.h"
#include "player.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_INFO          4
#define STATE_MENU_SOUNDFX       5

//define game states (on main menu)
#define STATE_GAME_PLAYING       8
#define STATE_GAME_PAUSE         9
#define STATE_GAME_OVER          10

Arduboy arduboy;
SimpleButtons buttons (arduboy);
Sprites sprites(arduboy);


unsigned char gameState = STATE_MENU_MAIN;
boolean soundYesNo;
int menuSelection;
byte currentRoom;
int currentRoomY;
byte level;
byte selectorX = 17;
byte selectorX2 = 35;
byte counter = 0;
unsigned long scorePlayer;
byte tyle;

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;
  arduboy.initRandomSeed();
  gameState = STATE_MENU_INTRO;
  gameState = STATE_MENU_MAIN;
  menuSelection = STATE_MENU_PLAY;
  Serial.begin(9600);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.clearDisplay();
  switch (gameState)
  {
    case STATE_MENU_INTRO:
      arduboy.drawBitmap(0, 8, TEAMarg2, 128, 48, WHITE);
      counter++;
      if (counter > 180) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_MAIN:
      // show the splash art
      arduboy.drawBitmap(0, 0, titlescreen, 128, 64, WHITE);
      arduboy.drawBitmap(17, 56, mainMenuBitmap, 93, 8, WHITE);
      if (arduboy.everyXFrames(2))
      {
        selectorX++;
        selectorX2--;
      }
      if (selectorX > 34)selectorX = 17;
      if (selectorX2 < 18)selectorX2 = 35;
      sprites.drawBitmap(selectorX + ((menuSelection - 2) * 24), 56, selectorPlusMask, NULL, 3, 8, SPRITE_PLUS_MASK);
      sprites.drawBitmap(selectorX2 + ((menuSelection - 2) * 24), 56, selectorPlusMask, NULL, 3, 8, SPRITE_PLUS_MASK);
      if (buttons.justPressed(RIGHT_BUTTON) && (menuSelection < 5)) menuSelection++;
      if (buttons.justPressed(LEFT_BUTTON) && (menuSelection > 2)) menuSelection--;
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = menuSelection;
      Serial.println(stageRoom[0].enemiesActive, BIN);
      break;
    case STATE_MENU_HELP: // QR code
      arduboy.drawBitmap(32, 0, qrCode_bitmap, 64, 64, WHITE);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_INFO: // infoscreen
      arduboy.drawBitmap(16, 20, info_bitmap, 96, 24, WHITE);
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_MENU_SOUNDFX: // soundconfig screen
      arduboy.drawBitmap(0, 0, titlescreen, 128, 64, WHITE);
      arduboy.drawBitmap(17, 56, soundMenuBitmap, 93, 8, WHITE);
      if (arduboy.everyXFrames(2))
      {
        selectorX++;
        selectorX2--;
      }
      if (selectorX > 34)selectorX = 17;
      if (selectorX2 < 18)selectorX2 = 35;
      sprites.drawBitmap(selectorX + (soundYesNo * 24)+40, 56, selectorPlusMask, NULL, 3, 8, SPRITE_PLUS_MASK);
      sprites.drawBitmap(selectorX2 + (soundYesNo * 24)+40, 56, selectorPlusMask, NULL, 3, 8, SPRITE_PLUS_MASK);
      if (buttons.justPressed(RIGHT_BUTTON)) soundYesNo = true;
      if (buttons.justPressed(LEFT_BUTTON)) soundYesNo = false;
      if (buttons.justPressed(A_BUTTON | B_BUTTON))
      {
        arduboy.audio.save_on_off();
        gameState = STATE_MENU_MAIN;
      }
      if (soundYesNo == true) arduboy.audio.on();
      else arduboy.audio.off();
      break;
    case STATE_MENU_PLAY:
      scorePlayer = 1234567;
      currentRoom = 0;
      currentRoomY = -14;
      level = 1;
      buildRoom(currentRoom, level);
      enterRoom(currentRoom, level);
      player.reset();
      gameState = STATE_GAME_PLAYING;
      break;
    case STATE_GAME_PLAYING:
      if (arduboy.everyXFrames(2))checkInputs();
      checkOrderOfObjects(currentRoom, level);
      updateRoom();
      updateHUD();
      //Serial.println(translateXYToTilePlayer(player.x, player.y));
      break;
    case STATE_GAME_OVER:
      arduboy.drawBitmap(0, 0, gameOverBitmap, 128, 64, WHITE);
      scoreDraw();
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
      break;
    case STATE_GAME_PAUSE:
      arduboy.drawBitmap(0, 0, pause, 128, 64, WHITE);
      scoreDraw();
      if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_GAME_PLAYING;
      break;
  }
  arduboy.display();
}

void scoreDraw()
{
  char buf[7];
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    sprites.drawBitmap(43 + (6 * i), 54, number0, NULL, 5, 8, SPRITE_IS_MASK);
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
    sprites.drawBitmap(43 + (pad * 6) + (6 * i), 54, numbers[digit], NULL, 5, 8, SPRITE_IS_MASK);

  }
}

