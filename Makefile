all: compile

compile:
	avr-gcc -Wall main.c joystick.c cd32.c mouse.c -std=c99 -O1 -mmcu=atmega8

flash: compile
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2 -U flash:w:a.out

fuse:
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2\
      -U lfuse:w:0xe2:m\
      -U hfuse:w:0xd9:m 

