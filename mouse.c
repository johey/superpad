#include "mouse.h"

#define STATE  0b00110011
#define QSTATE 0b01100110

void moveX(uint8_t *state) {
  if (!signalDIR(SNESPAD_DIR_LEFT)) {
    *state = rotateRight(*state);
  }
  if (!signalDIR(SNESPAD_DIR_RIGHT)) {
    *state = rotateLeft(*state);
  }
  if (STATE & *state) setHigh(AMIGA_H_PULSE); else setLow(AMIGA_H_PULSE);
  if (QSTATE & *state) setHigh(AMIGA_HQ_PULSE); else setLow(AMIGA_HQ_PULSE);
}

void moveY(uint8_t *state) {
  if (!signalDIR(SNESPAD_DIR_UP)) {
    *state = rotateRight(*state);
  }
  if (!signalDIR(SNESPAD_DIR_DOWN)) {
    *state = rotateLeft(*state);
  }
  if (STATE & *state) setHigh(AMIGA_V_PULSE); else setLow(AMIGA_V_PULSE);
  if (QSTATE & *state) setHigh(AMIGA_VQ_PULSE); else setLow(AMIGA_VQ_PULSE);
}

void clickButton(uint8_t snesbutton, uint8_t amigabutton) {
  if (!signalSNES(snesbutton)) setLow(amigabutton); else setHigh(amigabutton);
}

void runMouse() {
  flash(AMIGA_DIR_RIGHT);
  uint8_t stateX = 1, stateY = 1;

  setOutput(AMIGA_FIRE_CLK);
  setOutput(AMIGA_SEL);
  while (1) {
    
    moveX(&stateX);
    moveY(&stateY);
    clickButton(SNESPAD_Y, AMIGA_BUTTON_L);
    clickButton(SNESPAD_B, AMIGA_BUTTON_R);
    clickButton(SNESPAD_X, AMIGA_BUTTON_M);
    selectMode();

    _delay_ms(5);
  }
}

