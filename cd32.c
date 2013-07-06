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

#include "cd32.h"
#include "joystick.h"

void runCd32() {
  setInput(AMIGA_FIRE_CLK);
  setInput(AMIGA_SEL);

  while (1) {
    // Waiting for joystick mode
    while(!signal(AMIGA_SEL));
    if (signal(AMIGA_FIRE_CLK)) setHigh(AMIGA_DATA); 
    else setLow(AMIGA_DATA);

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

