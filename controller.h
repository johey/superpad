#ifndef controller_h
#define controller_h
/* Clock Frequency = 1Mhz */
#define F_CPU 1000000UL

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

// Amiga machine at PORTD
#define AMIGA_DIR_LEFT    0 /* p3 */
#define AMIGA_DIR_RIGHT   1 /* p4 */
#define AMIGA_DIR_UP      2 /* p1 */
#define AMIGA_DIR_DOWN    3 /* p2 */
#define AMIGA_SEL         4 /* p5 */
#define AMIGA_FIRE_CLK    5 /* p6 */
#define AMIGA_DATA        6 /* p9 */

// SNES direction buttons at PORTC
#define SNESPAD_DIR_LEFT  0
#define SNESPAD_DIR_RIGHT 1
#define SNESPAD_DIR_UP    2
#define SNESPAD_DIR_DOWN  3

// SNES pad buttons at PORTB
#define SNESPAD_LEFT      0
#define SNESPAD_RIGHT     1
#define SNESPAD_SELECT    2
#define SNESPAD_START     3 /* paus   */
#define SNESPAD_A         4 /* blue   */
#define SNESPAD_B         5 /* red    */
#define SNESPAD_X         6 /* yellow */
#define SNESPAD_Y         7 /* green  */

#define setHigh(button)   (PORTD |=  (1 << (button))) 
#define setLow(button)    (PORTD &= ~(1 << (button)))
#define setOutput(button) (DDRD  |=  (1 << (button))) 
#define setInput(button)  (DDRD  &= ~(1 << (button))) 
#define signal(button)    ((PIND >> button) & 1)

#define waitHighClock() while(!signal(AMIGA_FIRE_CLK))
#define waitLowClock() while(signal(AMIGA_FIRE_CLK))

#define signalSNES(button) ((PINB >> button) & 1)
#define signalDIR(button) ((PINC >> button) & 1)

int selectMode();

#endif

