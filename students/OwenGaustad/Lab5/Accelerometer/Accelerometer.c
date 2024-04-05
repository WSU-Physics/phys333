// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
// ---------------
//   Pin Defines
// ---------------
#define LED_PORT                PORTD
#define LED_DDR                 DDRD
#define LED_PORT2               PORTB
#define LED_DDR2                DDRB

#define LED2                    PD2   //Pin 2 
#define LED3                    PD3   //Pin 3 
#define LED4                    PD4   //Pin 4 
#define LED5                    PD5   //Pin 5 
#define LED6                    PD6   //Pin 6 
#define LED7                    PD7   //Pin 7 
#define LED8                    PB0   //Pin 8 
#define LED9                    PB1   //Pin 9 

int main(void) {
  char serialCharacter;

  // -------- Inits --------- //
  LED_DDR |= 0b11111100;                 /* set up LEDs for output */
  LED_DDR2 |= 0b00000011;                /* set up LEDs for output */
  printString("Hello World!\r\n");       /* to test */
  initUSART();
  
  // ------ Event loop ------ //
  while (1) {
    serialCharacter = receiveByte();    //recieves input from pin 0 and turns it into Ascii number
    printString("\n");                  //Prints new line

    while(serialCharacter != 'R'){      
      transmitByte(serialCharacter);
      serialCharacter = receiveByte();
    }
  }
  return 0;
}