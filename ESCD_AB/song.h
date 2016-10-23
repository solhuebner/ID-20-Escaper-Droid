#ifndef SONG_H
#define SONG_H

#define Song const uint8_t PROGMEM

Song music[] = {                // total song in bytes = 61
  //                            // setup bytes 21
  8,                            // Number of tracks
  0, 0,                         // Address of track 0
  4, 0,                         // Address of track 1
  8, 0,                         // Address of track 2
  13, 0,                        // Address of track 3
  21, 0,                        // Address of track 4
  42, 0,                        // Address of track 5
  56, 0,                        // Address of track 6
  66, 0,                        // Address of track 7
  2,                            // Channel 0 entry track (PULSE)
  1,                            // Channel 1 entry track (SQUARE)
  0,                            // Channel 2 entry track (TRIANGLE)
  3,                            // Channel 3 entry track (NOISE)

  //"Track 0"                   // ticks = 64, bytes = 5
  0x40, 0,                      // FX: SET VOLUME: volume = 0
  0x9F + 63,                    // DELAY: 63 ticks
  0xFE,                         // RETURN

  //"Track 1"                   // ticks = 2048, bytes = 4
  0xFD, 3, 4,                   // REPEAT: count = 4 - track = 4  (4 * 512 ticks)
  0xFE,                         // RETURN

  //"Track 2"                   // ticks = 2048, bytes = 5
  0xFD, 31, 6,                  // REPEAT: count = 32 - track = 5  (32 * 64 ticks)
  0x00,                         // NOTE OFF
  0xFE,                         // RETURN

  //"Track 3"                   // ticks = 2048, bytes = 7
  0xFD, 7,  0,                  // REPEAT: count = 8 - track = 8 (8 *64 ticks)
  0x9F + 8,                     // DELAY: 4 ticks
  0xFD, 23, 7,                  // REPEAT: count = 24 - track = 8 (24 *64 ticks)
  0xFE,                         // RETURN

  //"Track 4"                   // ticks = 512, bytes = 21
  0xFD, 1, 5,                   // REPEAT: count = 2 - track = 5  (2 * 64 ticks)
  0x4B, 3,                      // FX: ADD TRANSPOSITION: notes = 3
  0xFD, 1, 5,                   // REPEAT: count = 2 - track = 5  (2 * 64 ticks)
  0x4B, -1,                     // FX: ADD TRANSPOSITION: notes = 3
  0xFD, 1, 5,                   // REPEAT: count = 2 - track = 5  (2 * 64 ticks)
  0x4B, 3,                      // FX: ADD TRANSPOSITION: notes = 3
  0xFD, 1, 5,                   // REPEAT: count = 2 - track = 5  (2 * 64 ticks)
  0x4B, -5,                     // FX: ADD TRANSPOSITION: notes = 3
  0xFE,                         // RETURN

  //"Track 5"                   // ticks = 64, bytes = 14
  0x00 + 49,                    // NOTE ON: note = 49 (delay 1 tick)
  0x40, 63,                     // FX: SET VOLUME: volume = 63
  0x41, -16,                    // FX: VOLUME SLIDE ON: steps = -8
  0x9F + 16,                    // DELAY: 16 ticks
  0x40, 16,                     // FX: SET VOLUME: volume = 16
  0x41, -4,                     // FX: VOLUME SLIDE ON: steps = -4
  0x9F + 4,                     // DELAY: 4 ticks
  0x43,                         // FX: VOLUME SLIDE OFF
  0x9F + 43,                    // DELAY: 43 ticks
  0xFE,                         // RETURN

  //"track 6"                   // ticks = 64, bytes = 10
  0x00 + 13,                    // NOTE ON: note = 23 (delay 1 tick)
  0x40, 32,                     // FX: SET VOLUME: volume = 32
  0x4E, 1, 0x00 + 0x00 + 30,    // SET TREMOLO OR VIBRATO: depth = 16 / retrig = OFF / TorV = TREMOLO / rate = 3
  0x9F + 62,                    // DELAY: 62 ticks
  0x4F,                         // TREMOLO OR VIBRATO OFF
  0x9F + 1,                     // DELAY: 1 ticks
  0xFE,                         // RETURN

  //"track 7"                   // ticks = 64, bytes = 20
  0x40, 32,                     // FX: SET VOLUME: volume = 32
  0x9F + 1,                     // DELAY: ticks = 1
  0x40,  0,                     // FX: SET VOLUME: volume = 0
  0x9F + 15,                    // DELAY: ticks = 15

  0x40, 32,                     // FX: SET VOLUME: volume = 32
  0x9F + 1,                     // DELAY: ticks = 1
  0x40,  0,                     // FX: SET VOLUME: volume = 0
  0x9F + 15,                    // DELAY: ticks = 15

  0x40, 32,                     // FX: SET VOLUME: volume = 32
  0x41, -2,                     // FX: VOLUME SLIDE ON: steps = -2
  0x9F + 16,                    // DELAY: ticks = 16
  0x43,                         // FX: VOLUME SLIDE OFF
  0x9F + 16,                    // DELAY: ticks = 16
  0xFE,                         // RETURN

};

#endif
