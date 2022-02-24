// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // -------- Inits --------- //
  /* Data Direction Register D:
    writing a one to the bit
    enables output. */
  DDRD = 0xff;
  int _delay_ = 500;

  // ------ Event loop ------ //
  while (1) {
    PORTD = 0b00000001;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
    PORTD = 0b00000010;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
    PORTD = 0b00000100;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
    PORTD = 0b00001000;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
    PORTD = 0b00010000;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
    PORTD = 0b00100000;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
    PORTD = 0b01000000;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
    PORTD = 0b10000000;
    _delay_ms(_delay_);
    PORTD = 0;
    _delay_ms(_delay_);
  }
  return (0);
}
