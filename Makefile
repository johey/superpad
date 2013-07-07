#########################################################################
# Superpad - a SNES/SFC joypad conversion to the Amiga platform         #
# Copyright (C) 2013  Johan Svensson                                    #
#                                                                       #
# This program is free software: you can redistribute it and/or modify  #
# it under the terms of the GNU General Public License as published by  #
# the  Free  Software  Foundation, either version 3 of the License, or  #
# any later version.                                                    #
#                                                                       #
# This program is distributed  in the hope that it will be useful, but  #
# WITHOUT   ANY  WARRANTY;   without  even  the  implied  warranty  of  #
# MERCHANTABILITY  or  FITNESS  FOR  A  PARTICULAR  PURPOSE.  See  the  #
# GNU General Public License for more details.                          #
#                                                                       #
# You should  have received a copy  of the  GNU General Public License  #
# along with this program. If not, see <http://www.gnu.org/licenses/>.  #
#########################################################################

all: compile

compile:
	avr-gcc -Wall main.c joystick.c cd32.c mouse.c twoway.c -std=c99 -O1 -mmcu=atmega8

flash: compile
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2 -U flash:w:a.out

# 2MHz = lfuse:w:0xe2:m
# 8MHz = lfuse:w:0xc4:m
fuse:
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2\
      -U lfuse:w:0xe2:m\
      -U hfuse:w:0xd9:m\

