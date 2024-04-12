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

    PORTD = 0b00000001;          /* Turn on first LED bit/pin in PORTB */
    _delay_ms(1000);                                           /* wait */

    PORTD = 0b00000010;          /* Turn off all B pins, including LED */
    _delay_ms(1000);                                           /* wait */

    PORTD = 0b00000100;
    _delay_ms(1000);

    PORTD = 0b00001000;
    _delay_ms(1000);

    PORTD = 0b00010000;
    _delay_ms(1000);

    PORTD = 0b00100000;
    _delay_ms(1000);

    PORTD = 0b01000000;
    _delay_ms(1000);

    PORTD = 0b10000000;
    _delay_ms(1000);

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}