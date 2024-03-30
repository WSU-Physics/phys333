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

  // Data Direction Registers
  DDRB |= 0b11111100;  // Writing a 1 to the pin makes it an output
  DDRB |= 0b11111100;  // This seems to be a repeated line; you may want to check it.

  initUSART();
   printString("Hello World!\r\n"); /* to test */


  while (1) {

    serialCharacter = receiveByte();
// display ascii/numeric value of character
    LED_PORT = serialCharacter;
    PORTD = serialCharacter << 2;
    PORTB = serialCharacter >> 6;


// Print new line for every value.
    if(serialCharacter == 'R') printString("Inch\n");
    transmitByte(serialCharacter);
  }
 // End event loop
  return 0;
}
