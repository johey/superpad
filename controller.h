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

#ifndef controller_h
#define controller_h

/* Clock Frequency = 1Mhz */
#define F_CPU 2000000UL

#include <inttypes.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

// Amiga machine at PORTD, joystick mode
#define AMIGA_DIR_LEFT      1 /* p3 */
#define AMIGA_DIR_RIGHT     2 /* p4 */
#define AMIGA_DIR_UP        4 /* p1 */
#define AMIGA_DIR_DOWN      8 /* p2 */
#define AMIGA_SEL          16 /* p5 */
#define AMIGA_FIRE_CLK     32 /* p6 */
#define AMIGA_DATA         64 /* p9 */

// Amiga machine at PORTD, mouse mode
#define AMIGA_VQ_PULSE      1 /* p3 */
#define AMIGA_HQ_PULSE      2 /* p4 */
#define AMIGA_V_PULSE       4 /* p1 */
#define AMIGA_H_PULSE       8 /* p2 */
#define AMIGA_BUTTON_M     16 /* p5 */
#define AMIGA_BUTTON_L     32 /* p6 */
#define AMIGA_BUTTON_R     64 /* p9 */

// SNES direction buttons at PORTC
#define SNESPAD_DIR_LEFT    1
#define SNESPAD_DIR_RIGHT   2
#define SNESPAD_DIR_UP      4
#define SNESPAD_DIR_DOWN    8

// SNES pad buttons at PORTB
#define SNESPAD_LEFT        1
#define SNESPAD_RIGHT       2
#define SNESPAD_SELECT      4
#define SNESPAD_START       8 /* paus   */
#define SNESPAD_A          16 /* blue   */
#define SNESPAD_B          32 /* red    */
#define SNESPAD_X          64 /* yellow */
#define SNESPAD_Y         128 /* green  */

#define setHigh(button)   (PORTD |=  (button)) 
#define setLow(button)    (PORTD &= ~(button))
#define setOutput(button) (DDRD  |=  (button)) 
#define setInput(button)  (DDRD  &= ~(button)) 
#define signal(button)    (PIND & (button))

#define waitHighClock()\
  for (uint8_t i = 0xff; (!(PIND & 32)) && i; --i) selectMode()
#define waitLowClock()\
  for (uint8_t i = 0xff; (PIND & 32) && i; --i) selectMode()

#define rotateLeft(x) ((x >> 7) | (x << 1))
#define rotateRight(x) ((x >> 1) | (x << 7))

#define signalSNES(button) (PINB & (button))
#define signalDIR(button) (PINC & (button))

#define direction(snesdir, amigadir)\
  if (signalDIR(snesdir)) setHigh(amigadir); else setLow(amigadir)

#define button(snesbutton, amigabutton)\
  if (signalSNES(snesbutton)) setHigh(amigabutton); else setLow(amigabutton)

#define selectMode() if (!signalSNES(SNESPAD_SELECT)) return

#define abs16(val) ((val ^ (val >> 15)) - (val >> 15))

uint8_t modeSelector(uint8_t);

#endif

