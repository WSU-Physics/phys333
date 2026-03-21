// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRD |= 0b11111111;
  // I defined every pins on port D.
          
  // ------ Event loop ------ //
  while (1) {

    PORTD = 0b00000000;         //off at first
    _delay_ms(100);   

    PORTD = 0b00010000;         //turn on from right to left
    _delay_ms(100);                                           

    PORTD = 0b00110000;          
    _delay_ms(100);                                           

    PORTD = 0b01110000;          
    _delay_ms(100);                                           

    PORTD = 0b11110000;          
    _delay_ms(100);                                                 

    // These are the codes to turn LED on from right to left one by one.                                 
  }                                                
  return 0;                            
}
