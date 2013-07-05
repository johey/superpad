#include "cd32.h"
#include "joystick.h"

void runCd32() {
  setInput(AMIGA_FIRE_CLK);
  setInput(AMIGA_SEL);

  while (1) {
    // Waiting for joystick mode
    while(!signal(AMIGA_SEL));
    if (signal(AMIGA_FIRE_CLK)) setHigh(AMIGA_DATA); else setLow(AMIGA_DATA);


    // In Gamepad mode...

    // CD32 specific buttons
    shiftData(SNESPAD_A);
    direction(SNESPAD_DIR_DOWN, AMIGA_DIR_DOWN);
    shiftData(SNESPAD_B);
    direction(SNESPAD_DIR_RIGHT, AMIGA_DIR_RIGHT);
    shiftData(SNESPAD_X);
    direction(SNESPAD_DIR_UP, AMIGA_DIR_UP);
    shiftData(SNESPAD_Y);
    direction(SNESPAD_DIR_LEFT, AMIGA_DIR_LEFT);
    shiftData(SNESPAD_RIGHT);
    shiftData(SNESPAD_LEFT);
    shiftData(SNESPAD_START);

    // Last two bytes expected by the CD32 protocol
    waitLowClock();
    setHigh(AMIGA_DATA);
    waitHighClock();
    waitLowClock();
    setLow(AMIGA_DATA);
  }
}

