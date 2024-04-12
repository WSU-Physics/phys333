                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRD |= 0b11111111;            /* Data Direction Register D:
                                   writing a one to the bit
                                   enables output. */
  

  // ------ Event loop ------ //
  while (1) {

    PORTD = 0b1000000;          /* Turn on first LED bit/pin in PORTB */
    _delay_ms(200);                                           /* wait */

    PORTD = 0b01000000;        
    _delay_ms(200);         
    
    PORTD = 0b10100000;        
    _delay_ms(200);                                     /* wait */

    PORTD = 0b01010000;        
    _delay_ms(200);   

    PORTD = 0b10101000;        
    _delay_ms(200); 

    PORTD = 0b01010100;        
    _delay_ms(200);   

    PORTD = 0b10101010;        
    _delay_ms(200);  

    PORTD = 0b01010101;        
    _delay_ms(200); 

    PORTD = 0b00101011;        
    _delay_ms(200); 

     PORTD = 0b00010101;        
    _delay_ms(200); 

     PORTD = 0b00001011;        
    _delay_ms(200); 

    PORTD = 0b00000101;        
    _delay_ms(200); 

     PORTD = 0b00000011;        
    _delay_ms(200); 

     PORTD = 0b00000001;        
    _delay_ms(1000); 
  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}