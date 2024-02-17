// POV toy demo framework //

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// -------- Functions --------- //
void POVDisplay(uint8_t oneByte) {
  PORTD = oneByte;
  _delay_ms(2);
}

int main(void) {
  // -------- Inits --------- //
  DDRD = 0xff;                    /* Set up all of LED pins for output */
  // ------ Event loop ------ //
  while (1) {                                              /* mainloop */
    POVDisplay(0b00000001);
    _delay_ms(100);
    POVDisplay(0b00000010);
    _delay_ms(100);
    POVDisplay(0b00000100);
    _delay_ms(100);
    POVDisplay(0b00001000);
    _delay_ms(100);
    POVDisplay(0b00010000);
    _delay_ms(100);
    POVDisplay(0b00100000);
    _delay_ms(100);
    POVDisplay(0b01000000);
    _delay_ms(100);
    POVDisplay(0b10000000);
    _delay_ms(100);
    PORTD = 0;
  }                                                    /* end mainloop */
  return 0;
}