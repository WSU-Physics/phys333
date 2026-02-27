// POV toy demo framework //

//adapted by thea to be a heart

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
  while (1) { 
    POVDisplay(0b00000000);                                             /* mainloop */
    POVDisplay(0b00110000);
    POVDisplay(0b01111000);
    POVDisplay(0b11111100);
    POVDisplay(0b01111110);
    POVDisplay(0b00111111);
    POVDisplay(0b01111110);
    POVDisplay(0b11111100);
    POVDisplay(0b01111000);
    POVDisplay(0b00110000);
    POVDisplay(0b00000000);

    PORTD = 0;
    _delay_ms(10);
  }                                                    /* end mainloop */
  return 0;
}
