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
#include "mouse.h"
#include "twoway.h"
#include "controller.h"

uint8_t EEMEM savedMode;

uint8_t modeSelector(uint8_t current) {
  uint8_t old = current;
  while (!signalSNES(SNESPAD_SELECT)) {
    if (!signalSNES(SNESPAD_X)) current = 1; // CD32
    if (!signalSNES(SNESPAD_Y)) current = 0; // Joystick
    if (!signalSNES(SNESPAD_A)) current = 2; // Amiga mouse
    if (!signalSNES(SNESPAD_B)) current = 3; // Two ways joystick
  }
  if (old != current)
    eeprom_write_byte(&savedMode, current);
  return current;
}

int main(void) {
  uint8_t currentMode = eeprom_read_byte(&savedMode);

  /* B and C are all inputs, D is all output */
  DDRB = 0x00;
  DDRC = 0x00;
  DDRD = 0b11111111;
  PORTD = 0b11111111;

  /* Enable pull-up resistors of B and C */
  PORTB = 0xff;
  PORTC = 0xff;
  PORTD = 0xff;

  while (1) {
    switch(currentMode) {
      case 1:
        runCd32(); break;
      case 2:
        runMouse(); break;
      case 3:
        runTwoway(); break;
      case 0: default:
        runJoystick(); break;
    }
    currentMode = modeSelector(currentMode);
  }
}

