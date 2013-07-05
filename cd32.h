#ifndef cd32_h
#define cd32_h

#include "controller.h"

void runCd32();

#define datashift(button) ((PINB & (1 << button)) << (7 - button))

#define shiftData(button) waitLowClock(); if (signalSNES(button)) setHigh(AMIGA_DATA); else setLow(AMIGA_DATA); waitHighClock() 

#endif

