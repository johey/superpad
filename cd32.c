#include "cd32.h"

void setupCd32() {
  /* B and C are all inputs, D is all output */
  DDRB = 0x00;
  DDRC = 0x00;
  DDRD = 0b11111111;

  PORTD = 0b11111111;

  /* Enable pull-up resistors of B and C */
  PORTB = 0xff;
  PORTC = 0xff;
  PORTD = 0xff;

  /*                  
  directionLeft  = (PINC & 1)    PC0
  directionRight = (PINC & 2)    PC1
  directionUp    = (PINC & 4)    PC2
  directionDown  = (PINC & 8)    PC3
  buttonLeft     = (PINB & 1)    PB0
  buttonRight    = (PINB & 2)    PB1
  buttonSelect   = (PINB & 4)    PB2
  buttonStart    = (PINB & 8)    PB3
  buttonA blue   = (PINB & 16)   PB4
  buttonB red    = (PINB & 32)   PB5
  buttonX yellow = (PINB & 64)   PB6
  buttonY green  = (PINB & 128)  PB7


  3 green   left            4  PD0
  4 brown   right           8  PD1
  1 white   up              1  PD2
  2 blue    down            2  PD3
  5 yellow  red,load/shift 16  PD4
  6 orange  fire/clk       32  PD5
  7 red     5v
  8 black   gnd
  9 grey    button2,blue   64  PD6
  */

  setInput(AMIGA_FIRE_CLK);
  setInput(AMIGA_SEL);
}

void loopCd32() {
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

    if (!signalSNES(SNESPAD_SELECT))
      selectMode();

    // Last two bytes expected by the CD32 protocol
    waitLowClock();
    setHigh(AMIGA_DATA);
    waitHighClock();
    waitLowClock();
    setLow(AMIGA_DATA);
  }
    

  // Normal joystick mode
  //while (1) {
  //  direction(SNESPAD_DIR_DOWN, AMIGA_DIR_DOWN);
  //  direction(SNESPAD_DIR_RIGHT, AMIGA_DIR_RIGHT);
  //  direction(SNESPAD_DIR_UP, AMIGA_DIR_UP);
  //  direction(SNESPAD_DIR_LEFT, AMIGA_DIR_LEFT);
  //  button(SNESPAD_Y, AMIGA_FIRE_CLK);
  //  button(SNESPAD_Y, AMIGA_DATA);
  //}

}

