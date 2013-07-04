#ifndef cd32_h
#define cd32_h

#include "controller.h"

void setupCd32();
void loopCd32();

#define datashift(button) ((PINB & (1 << button)) << (7 - button))

#define shiftData(button) waitLowClock(); if (signalSNES(button)) setHigh(AMIGA_DATA); else setLow(AMIGA_DATA); waitHighClock() 

#define direction(snesdir, amigadir) if (signalDIR(snesdir)) setHigh(amigadir); else setLow(amigadir)

#define button(snesbutton, amigabutton) if (signalSNES(snesbutton)) setHigh(amigabutton); else setLow(amigabutton)

#endif

