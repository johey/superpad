#include "mouse.h"

#define STATE  0b00110011 // Amiga mouse pulse mask
#define QSTATE 0b01100110 // 90 degrees shifted pulse mask

#define SPEED_DIVIDER 64  // 1 to 128, higher means slower

//#define setupMouseMovement(state, snes, rotate)\
//  if (!signalDIR(snes)) {\
//    *state = rotate(*state);\
//  }
//  
#define moveMouse(mask, state, pulse)\
  if (mask & *state) setHigh(pulse); else setLow(pulse);
//
//void move(uint8_t *stateX, uint8_t *stateY, int16_t speedX, int16_t speedY) {
//  for (uint8_t n = abs16(speedX); n >= 0; --n) {
//    setupMouseMovement(stateX, SNESPAD_DIR_LEFT, rotateRight);
//    setupMouseMovement(stateX, SNESPAD_DIR_RIGHT, rotateLeft);
//    setupMouseMovement(stateY, SNESPAD_DIR_UP, rotateRight);
//    setupMouseMovement(stateY, SNESPAD_DIR_DOWN, rotateLeft);
//  }
//}
//
void clickButton(uint8_t snesbutton, uint8_t amigabutton) {
  if (!signalSNES(snesbutton)) setLow(amigabutton); else setHigh(amigabutton);
}

#define setSpeed(speed, dir1, dir2, diagonal)\
    moving1 = moving2 = 0;\
    if (!signalDIR(dir1)) { speed = (speed - acc < -limit ? speed : speed - acc); ++moving1; }\
    if (!signalDIR(dir2)) { speed = (speed + acc > limit ? speed : speed + acc); ++moving2; }\
    if (moving1 && moving2) diagonal = 1;\
    if (!moving1 && !moving2 && i % 8 == 0) speed /= 2
  
void runMouse() {
  // Signed speed value, positive=right/down, negative=left/up
  int16_t speedX = 0, speedY = 0;
  // Acceleration value, positive=accelerate, negative=decelerate
  int8_t acc;
  int16_t limit;
  int8_t moving1, moving2, diag1, diag2;
  int8_t i = 0;

  // On each update, multiply acc with speed unless limit is met.
  // By holding a direction, the respecive acc variable should
  // multiply with speed.

  uint8_t stateX = 1, stateY = 1;

  setOutput(AMIGA_FIRE_CLK);
  setOutput(AMIGA_SEL);
  while (1) {
    diag1 = diag2 = 0;
    limit = 190;
    acc = 7;
    if (!signalSNES(SNESPAD_RIGHT)) {
      limit = 400;
      acc = 24;
    }
    if (!signalSNES(SNESPAD_LEFT) && i % 8 == 0) {
      speedX /= 2;
      speedY /= 2;
    }
    setSpeed(speedX, SNESPAD_DIR_LEFT, SNESPAD_DIR_RIGHT, diag1);
    setSpeed(speedY, SNESPAD_DIR_UP, SNESPAD_DIR_DOWN, diag2);

    for (uint8_t i = (abs16(speedX) / SPEED_DIVIDER); i > 0; --i) {
      stateX = speedX > 0 ? rotateLeft(stateX) : rotateRight(stateX);
      moveMouse(STATE, &stateX, AMIGA_H_PULSE);
      moveMouse(QSTATE, &stateX, AMIGA_HQ_PULSE);
    }

    for (uint8_t i = (abs16(speedY) / SPEED_DIVIDER); i > 0; --i) {
      stateY = speedY > 0 ? rotateLeft(stateY) : rotateRight(stateY);
      moveMouse(STATE, &stateY, AMIGA_V_PULSE);
      moveMouse(QSTATE, &stateY, AMIGA_VQ_PULSE);
    }
    clickButton(SNESPAD_B, AMIGA_BUTTON_L);
    clickButton(SNESPAD_A, AMIGA_BUTTON_R);
    clickButton(SNESPAD_X, AMIGA_BUTTON_M);
    selectMode();

    _delay_ms(20 + (diag1 && diag2) ? 6 : 0);
    --i;
  }
}

