all:
	avr-gcc main.c joystick.c cd32.c -std=c99 -O2 -mmcu=atmega8
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2 -U flash:w:a.out

