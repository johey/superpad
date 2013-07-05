#include "controller.h"
#include "cd32.h"
#include "joystick.h"


void modeSelector() {
  while (!signalSNES(SNESPAD_SELECT)) {
    mode(SNESPAD_X, runCd32);
    mode(SNESPAD_Y, runJoystick);
  }
}

int main(void) {
  /* B and C are all inputs, D is all output */
  DDRB = 0x00;
  DDRC = 0x00;
  DDRD = 0b11111111;

  PORTD = 0b11111111;

  /* Enable pull-up resistors of B and C */
  PORTB = 0xff;
  PORTC = 0xff;
  PORTD = 0xff;

  run = &runJoystick;
  while(1) {
    if (run == &runJoystick) runJoystick();
    if (run == &runCd32) runCd32();
  }
}

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
