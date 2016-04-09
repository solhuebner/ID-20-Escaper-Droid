/*
 Escaper Droid: http://www.team-arg.org/escd-manual.html

 Arduboy version 0.4d:  http://www.team-arg.org/escd-downloads.html

 MADE by TEAM a.r.g. : http://www.team-arg.org/About.html

 2016 - JO3RI - STG

 Game License: MIT : https://opensource.org/licenses/MIT

 */

//determine the game
#define GAME_ID 20

#include "Arglib.h"
#include "globals.h"
#include "menu.h"
#include "game.h"
#include "room.h"
#include "enemies.h"
#include "inputs.h"
#include "player.h"


typedef void (*FunctionPointer) ();
FunctionPointer mainGameLoop[] =
{
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;
  arduboy.initRandomSeed();
  gameState = 1;
  menuSelection = 3;
  Serial.begin(9600);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.clearDisplay();
  mainGameLoop[gameState]();
  arduboy.display();
};

