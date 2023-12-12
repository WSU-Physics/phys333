// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
// -------- Functions --------- //
void POVDisplay(uint8_t oneByte) {
  PORTD = oneByte;

  _delay_ms(20); //experimenting to see the pattern

}
int main(void) {
  // -------- Inits --------- //
  DDRD = 0xff; /* Set up all of LED pins for output */
  // ------ Event loop ------ //
  while (1) { /* mainloop */
    POVDisplay(0b01111110);
    _delay_ms(50);
    POVDisplay(0b10111101);
    _delay_ms(50);
    POVDisplay(0b11011011);
    _delay_ms(50);
    POVDisplay(0b11100111);
    _delay_ms(50);
    POVDisplay(0b11011011);
    _delay_ms(50);
    POVDisplay(0b11101101);
    _delay_ms(50);
    POVDisplay(0b11110110);
    _delay_ms(50);
    POVDisplay(0b11101101);
    _delay_ms(50);
    POVDisplay(0b11011011);
    _delay_ms(50);
    POVDisplay(0b10110111);
    _delay_ms(50);
    POVDisplay(0b01101111);
    _delay_ms(50);
    POVDisplay(0b10110111);
    _delay_ms(50);
    POVDisplay(0b11011011);
    _delay_ms(50);
    POVDisplay(0b11101101);
    _delay_ms(50);
    POVDisplay(0b11110110);
    _delay_ms(50);

    POVDisplay(0b11101101);
    _delay_ms(50);
    POVDisplay(0b11011011);
    _delay_ms(50);
    POVDisplay(0b10110111);
    _delay_ms(50);
    POVDisplay(0b01101111);
    _delay_ms(50);
    POVDisplay(0b10110111);
    _delay_ms(50);
    POVDisplay(0b11011011);
    _delay_ms(50);
    POVDisplay(0b11100111);
    _delay_ms(50);
    POVDisplay(0b11011011);
    _delay_ms(50);
    POVDisplay(0b10111101);
    _delay_ms(50);
    POVDisplay(0b01111110);
    _delay_ms(50);

    POVDisplay(0b00000000);
    _delay_ms(100);
    POVDisplay(0b11111111);
    _delay_ms(100);
    

    
    //PORTD = 0;
   // _delay_ms(100);
  } /* end mainloop */
  return (0);
}
