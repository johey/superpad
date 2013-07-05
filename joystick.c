#include "joystick.h"

void runJoystick() {
  setOutput(AMIGA_FIRE_CLK);
  setOutput(AMIGA_SEL);
  while (1) {
    direction(SNESPAD_DIR_DOWN, AMIGA_DIR_DOWN);
    direction(SNESPAD_DIR_RIGHT, AMIGA_DIR_RIGHT);
    direction(SNESPAD_DIR_UP, AMIGA_DIR_UP);
    direction(SNESPAD_DIR_LEFT, AMIGA_DIR_LEFT);
    button(SNESPAD_Y, AMIGA_FIRE_CLK);
    button(SNESPAD_B, AMIGA_DATA);

    selectMode();
  }
}

