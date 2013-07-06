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

#ifndef mouse_h
#define mouse_h

#include "controller.h"

void runMouse();

#define direction(snesdir, amigadir)\
  if (signalDIR(snesdir)) setHigh(amigadir); else setLow(amigadir)

#define button(snesbutton, amigabutton)\
  if (signalSNES(snesbutton)) setHigh(amigabutton); else setLow(amigabutton)

#endif

