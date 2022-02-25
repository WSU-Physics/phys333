

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// -------- Functions --------- //
void POVDisplay(uint8_t oneByte) {
  PORTD = oneByte;
  _delay_ms(100);//speed
}
void POVDisplay2(uint8_t oneByte) {
  PORTD = oneByte;
  _delay_ms(100);//speed
}

int main(void) {

  // -------- Inits --------- //
  DDRD = 0xff;                    /* Set up all of LED pins for output */
  // ------ Event loop ------ //
  while (1) {                                              /* mainloop */
    POVDisplay(0b10001000);
    POVDisplay(0b10000100);
    POVDisplay(0b00000010);
    POVDisplay(0b00000001);           
    PORTD = 0;


  }
  return 0;
}
