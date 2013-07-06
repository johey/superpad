/***********************************************************************\
* Superpad - a SNES/SFC joypad conversion to the Amiga platform         *
* Copyright (C) 2013  Johan Svensson                                    *
*                                                                       *
* This program is free software: you can redistribute it and/or modify  *
* it under the terms of the GNU General Public License as published by  *
* the  Free  Software  Foundation, either version 3 of the License, or  *
* any later version.                                                    *
*                                                                       *
* This program is distributed  in the hope that it will be useful, but  *
* WITHOUT   ANY  WARRANTY;   without  even  the  implied  warranty  of  *
* MERCHANTABILITY  or  FITNESS  FOR  A  PARTICULAR  PURPOSE.  See  the  *
* GNU General Public License for more details.                          *
*                                                                       *
* You should  have received a copy  of the  GNU General Public License  *
* along with this program. If not, see <http://www.gnu.org/licenses/>.  *
\***********************************************************************/

#include "mouse.h"

#define STATE  0b00110011 // Amiga mouse pulse mask
#define QSTATE 0b01100110 // 90 degrees shifted pulse mask

#define SPEED_DIVIDER 64  // 1 to 128, higher means slower

#define moveMouse(mask, state, pulse)\
  if (mask & *state) setHigh(pulse); else setLow(pulse);

void clickButton(uint8_t snesbutton, uint8_t amigabutton) {
  if (!signalSNES(snesbutton)) setLow(amigabutton); else setHigh(amigabutton);
}

#define setSpeed(speed, dir1, dir2, diagonal)\
  moving1 = moving2 = 0;\
  if (!signalDIR(dir1)) {\
    speed = (speed - acc < -limit ? speed : speed - acc); ++moving1; }\
  if (!signalDIR(dir2)) {\
    speed = (speed + acc > limit ? speed : speed + acc); ++moving2; }\
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

