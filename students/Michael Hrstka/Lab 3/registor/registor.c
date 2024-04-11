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
    PORTD = 0;
    for (int i = 0; i < 256; i++){
      PORTD++;
      _delay_ms(100);
    }
    PORTD = 1;
    for (int i = 0; i < 9 * 4; i++){

      PORTD = PORTD == 0b00000000 ? 1 : PORTD << 1;
      _delay_ms(100);
    }
    PORTD = 1;
    _Bool right = 0;
    for (int i = 0; i < 7 * 6; i++){
      if(PORTD == 1){
        right = 0;
      }
      if(PORTD == 0b10000000){
        right = 1;
      }
      PORTD = right ? PORTD >> 1 : PORTD << 1;
      _delay_ms(100);
    }

  }
  return 0;                            /* This line is never reached */
}
