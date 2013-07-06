Superpad
========

Modify a SNES/SFC joypad for use with Amiga with usefull unique features. AVR ATmega code. Build with avr-gcc, licenced under GPLv3.

## Ultimate control over Amiga games
With the Superpad hardware/software project, you will get a SNES joypad (or any clone) to act like an ultimate controller for the Amiga (and likely other systems with DB9 joystick connectors). It is more than a stupid adapter. With the ATMega microcontroller, it currently provides the following features:
* pressing SELECT plus one of the A, B, X and Y buttons changes the mode of the joypad
* mode Y is normal two button joystick mode where Y and B correspond to fire 1 and 2, X and A are autofire versions of the respective fire buttons, L and R are "autofire" functions for left and right direction pad (imagine yourself playing pr0no games this way ;-) )
* mode X is CD32 joypad simulation, where all buttons are mapped to their corresponding physical location of the original CD32 controller, except for the SELECT button which still is the mode selector
* mode A is mouse simulation, practical to have when two Superpads are connected and you temporarily need a mouse for starting a new game or booting with early boot selector. Mapping are: B=LMB, A=RMB, X=MMB, R=accelerate, B=slow down. It is actually quite convenient to control the mouse this way. You can even play Lemmings or adventure games
* currently selected mode will be saved until you change, even after power off

Well, isn't this something? I have really designed the user interface and features to do exactly what I personally want. Should you have different preferences, feel free to ask me, or better, clone the project and fix it yourself.

The project name Superpad is stolen from the printing of the cheap Chinese third-party SNES joypad clone I have been using for this project. Sue me, mighty pirates! :-)

### This mod currently involves quite some hackish methods, including
* disassembly of a SNES joypad and removing the original cable
* install an Atmel ATMega8-16PU into the controller
* solder a lead from each button to an input pin of the ATMega
* install a new cable fully connected to a 9 pin DSUB connector to output pins of the ATMega
* and of course, program the ATMega with the superpad software.

### Future ideas
* demessify parts of the code, replacing polling with interrupts (requires hardware modification), maybe rewrite timing critical parts in assembler
* install the ATMega at the end of the cable instead of into the pad. This requires the microcontroller to decode the SNES encoded signal, but there are two advantages: first you don't need to to messy things to your controller, and second, you can reuse the original controller cable with only five leads. The tricky part is that it adds another timing critical moment for the SNES decoding, as if the CD32 encoding simulation wouldn't be enough.
* base on arduino bootloader to ease the reprogramming process
* add support for reconfiguring the buttons without reprogramming
* add explicit support for different platforms like Atari and C64
* create detailed rebuilding instructions
* create pre-rebuilt units for sale???
