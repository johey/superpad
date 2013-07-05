all:
	avr-gcc main.c joystick.c cd32.c -std=c99 -O2 -mmcu=atmega8
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2 -U flash:w:a.out

fuse:
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2 -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m 

