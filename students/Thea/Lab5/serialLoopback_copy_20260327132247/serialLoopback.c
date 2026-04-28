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

#define LED_DDR1 DDRD
#define LED_DDR2 DDRB
#define LED_PORT1 PORTD
#define LED_PORT2 PORTB

int main(void) {
  char serialCharacter;

  // -------- Inits --------- //
  LED_DDR1 |= 0b11111100;                          /* set up LEDs for output */
  LED_DDR2 |= 0b00000011;
  initUSART();
  printString("Hello World!\r\n");                          /* to test */

  // ------ Event loop ------ //
  while (1) {

    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    LED_PORT1 = (serialCharacter << 2);
    LED_PORT2 = (serialCharacter >> 6);
    _delay_ms(500);
                           /* display ascii/numeric value of character */

  }                                                  /* End event loop */
  return 0;
}