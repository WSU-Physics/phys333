// POV toy demo framework //

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// -------- Functions --------- //
void POVDisplay(uint8_t oneByte) {
  PORTD = oneByte;
  _delay_ms(200);
}

int main(void) {
  // -------- Inits --------- //
  DDRD = 0xff;                    /* Set up all of LED pins for output */
  // ------ Event loop ------ //
  while (1) {                                              /* mainloop */
    POVDisplay(0b00000011);
    POVDisplay(0b00001100);
    POVDisplay(0b00110000);
    POVDisplay(0b01100000);
    POVDisplay(0b11000000);
    POVDisplay(0b01100000);
    POVDisplay(0b00110000);
    POVDisplay(0b00001100);
    POVDisplay(0b00000011);
    PORTD = 0;
    _delay_ms(100);
  }                                                    /* end mainloop */
  return 0;
}
