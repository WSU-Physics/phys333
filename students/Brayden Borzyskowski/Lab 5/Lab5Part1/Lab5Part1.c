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
  // can't use all of D for LED's because 0 and 1 are rx and tx
  // use 0 and 1 for serial
  // use 2-7 + pin 8 & pin 9 for LED's
  // (i.e. PD2-7 and PB0-1)

  //DDRD = 0xff - 3;
  //DDRD = 0xff << 2;
  DDRD |= 0b11111100;
  DDRB |= 0b00000011;
  //DDRD = 0xfc;                          /* set up LEDs for output */
  initUSART();
  printString("Hello World!\r\n");      /* to test */

  // ------ Event loop ------ //
  while (1) {

    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    LED_PORT = serialCharacter;
    PORTD = serialCharacter << 2;
    PORTB = serialCharacter >> 6;
    
     /* display ascii/numeric value of character */
  } /* End event loop */
  return (0); 
}

