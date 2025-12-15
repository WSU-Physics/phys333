/*
A simple test of serial-port functionality.
Takes in a character at a time and sends it right back out,
 displaying the ASCII value on the LEDs.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

int main(void) {
  char serialCharacter;

  // -------- Inits --------- //
// cant use all of D for LEDs because 0 and 1 are rx and tx
// use 0 and 1 for serial 
// use 2 - 7 + 8 & 9 for LEDs 
// (i.e. PD2-7 and PB0-1)

  DDRD |= 0x11111100;                            /* set up LEDs for output */
  DDRB |= 0b00000011;

  initUSART();
  //printString("Hello World!\r\n");                          /* to test */

  // ------ Event loop ------ //
  while (1) {
    
    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    LED_PORT = serialCharacter;

    PORTD = serialCharacter << 2;
    PORTB = serialCharacter >> 6; 


                           /* display ascii/numeric value of character */

  }                                                  /* End event loop */
  return 0;
}