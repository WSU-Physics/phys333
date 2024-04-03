#include <avr/io.h>
#include <util/delay.h> 



int main(void) {
  // ---- Inits ---- //
  PORTD |= (1 << PD2);  
  DDRB = 0xff;

  while (1) {
    if (bit_is_clear(PIND, PD2)) {
      
      PORTD = 0b00111100;
    }
      else {
        PORTD = 0b11000011;
      }
    }
    return (0);
}