

// ------- Preamble -------- //
#include <avr/io.h>

#include <util/delay.h>
#define DEBOUNCE_TIME  1000                            /* microseconds */

uint8_t debounceLeft(void) {
  if (bit_is_clear(PINB, PB5)) {      /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, PB5)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

uint8_t debounceRight(void) {
  if (bit_is_clear(PINB, PB4)) {      /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, PB4)) {            
      return (1);
    }
  }
  return 0;
}

int main(void) {
  uint8_t buttonWasPressedLeft=0;                                
  uint8_t buttonWasPressedRight=0; 

  PORTB |= (1 << PB5);     /* enable the pullup on the button */
  PORTB |= (1 << PB4);        

  DDRD = 0xff; //LEDs              

  while (1) {
    if (debounceLeft()) {                       
      if (buttonWasPressedLeft == 0) {     
        PORTD ^= 0b00001111;                       
        buttonWasPressedLeft = 1;                      
      }
    }
    else {                                
      buttonWasPressedLeft = 0;                        
    }

    if (debounceRight()) {                        
      if (buttonWasPressedRight == 0) {     
        PORTD ^= 0b11110000;                        
        buttonWasPressedRight = 1;                      
      }
    }
    else {                                
      buttonWasPressedRight = 0;                        
    }
  }                                                 
  return 0; 
}