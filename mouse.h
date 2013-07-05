#ifndef mouse_h
#define mouse_h

#include "controller.h"

void runMouse();

#define direction(snesdir, amigadir) if (signalDIR(snesdir)) setHigh(amigadir); else setLow(amigadir)

#define button(snesbutton, amigabutton) if (signalSNES(snesbutton)) setHigh(amigabutton); else setLow(amigabutton)

#endif

