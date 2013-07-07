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

#include "joystick.h"

void runJoystick() {
  setOutput(AMIGA_FIRE_CLK);
  setOutput(AMIGA_SEL);
  while (1) {
    direction(SNESPAD_DIR_DOWN, AMIGA_DIR_DOWN);
    direction(SNESPAD_DIR_RIGHT, AMIGA_DIR_RIGHT);
    direction(SNESPAD_DIR_UP, AMIGA_DIR_UP);
    direction(SNESPAD_DIR_LEFT, AMIGA_DIR_LEFT);
    button(SNESPAD_B, AMIGA_FIRE_CLK);
    button(SNESPAD_A, AMIGA_DATA);

    selectMode();
  }
}

