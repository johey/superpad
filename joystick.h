#ifndef joystick_h
#define joystick_h

#include "controller.h"

void runJoystick();

#define direction(snesdir, amigadir) if (signalDIR(snesdir)) setHigh(amigadir); else setLow(amigadir)

#define button(snesbutton, amigabutton) if (signalSNES(snesbutton)) setHigh(amigabutton); else setLow(amigabutton)

#endif

