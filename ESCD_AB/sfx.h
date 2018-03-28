#ifndef SFX_H
#define SFX_H

const PROGMEM struct sfx0_data {
  uint8_t fmt;
  uint8_t pattern0[12];
} sfx0 = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(32),
    ATM_CMD_M_SET_VOLUME(127),
    ATM_CMD_M_SLIDE_VOL_ON(-8),
    ATM_CMD_I_NOTE_F6,
    ATM_CMD_M_DELAY_TICKS(5),
    ATM_CMD_I_NOTE_G6,
    ATM_CMD_M_DELAY_TICKS(11),
    ATM_CMD_I_STOP,
  },
};

#endif
