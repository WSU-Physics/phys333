// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
// ---------------
//   Pin Defines
// ---------------

#define LED_PORT                PORTD
#define LED_DDR                 DDRD

#define SERIAL1                 PD0
#define SERIAL2                 PD1
#define LED2                    PD2
#define LED3                    PD3
#define LED4                    PD4
#define LED5                    PD5
#define LED6                    PD6
#define LED7                    PD7

#define LED_PORT2               PORTB
#define LED_DDR2                DDRB

#define LED8                    PB0
#define LED9                    PB1

int main(void) {
  char serialCharacter;

  // -------- Inits --------- //
  LED_DDR |= 0b11111100;                            /* set up LEDs for output */
  LED_DDR2 |= 0b00000011;
  
  initUSART();
  printString("Hello World!\r\n");                          /* to test */

  // ------ Event loop ------ //
  while (1) {
    serialCharacter = receiveByte();
    printString("\n"); 
    while(serialCharacter != 'R'){
      transmitByte(serialCharacter);
      serialCharacter = receiveByte();
    }
  }
  return 0;
}