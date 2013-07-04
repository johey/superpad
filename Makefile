all:
	avr-gcc controller.c main.c cd32.c -O2 -mmcu=atmega8
	avrdude -p m8 -P /dev/ttyUSB0 -c stk500v2 -U flash:w:a.out

