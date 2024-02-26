//Lab 4 

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#define DEBOUNCE_TIME 1000

// Button Debouncer 
uint8_t debounce(void) {
  if (bit_is_clear(PINB,PB0)) {
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PINB,PB0)){
      return(1);
    }
  }
  return(0);
}


//Part 1 - ToggleButton

int main(void) {

  // -------- Inits --------- //
  uint8_t buttonpressed;
  PORTB |= (1<<PB0);
  DDRD = (1<<PD0); 
  /*
  DDRD |= 0b11111111;  
  DDRB |= 0b11111111;  
  */

  // ------ Event loop ------ //
  while (1) {
    if (debounce()){
    if (bit_is_clear(PINB, PB0)) {
      if (buttonpressed==0) {
        PORTD ^= (1<<PD0);
        buttonpressed=1;
      }
    }
    }
  
    else {
   buttonpressed=0;
    }
  }
    return(0);
}