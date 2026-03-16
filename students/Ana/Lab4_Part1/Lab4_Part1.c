

#include <avr/io.h>
#include <util/delay.h>
//#include "pinDefines.h"
#define DEBOUNCE_TIME 1000  //micros

/*
  uint8_t debounce(void) {
  if (bit_is_clear(PB4, BUTTON)) {
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PB4, BUTTON)) {
      return(1);
    }
  }
  return(0);
}
*/

int main (void) {
  DDRB = 0x00;  //setting register to input
  PORTB |= (1 << PB5);
  PORTB |= (1 << PB4);  //initialize pullup on input pin
  DDRD = 0xff;  //set up all LEDS for output

  while(1) {
    if(bit_is_clear(PINB, PB5) ) { //bit_is_clear(PINB, PB4)) { //if PORTB & (1<<PB4) == 0
      //PINB &= ~(1 << PB4);
      PORTD = 0b00000000; //pressed
    } else {
      //PORTB &= ~(1 << PB4);
      PORTD = 0b00001111; //not pressed
    }
    
    if(bit_is_clear(PINB, PB4) ) {
      //PINB &= ~( (1 << PB5) );
      PORTD = 0b10000000; //pressed
    } else {
      //PORTB &= ~( 1 << PB5);
      PORTD = 0b11110000; //not pressed
    }
    
  }
  
  return(0);
}