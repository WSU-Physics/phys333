// POV toy demo framework  adapted again again by james g //

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
    POVDisplay(0b10000000);       // lights up led 7
    _delay_ms(150);
    
    POVDisplay(0b01000000);       // turns off led 7, turns on 6
    _delay_ms(150);
    
    POVDisplay(0b00100000);       // turns off 6, on 5
    _delay_ms(150);

    POVDisplay(0b00010000);       // turns off 5, on 4
    _delay_ms(150);
    
    POVDisplay(0b00001000);       // wow you're never gonna guess what
    _delay_ms(150);
    
    POVDisplay(0b00000100);
    _delay_ms(150);
    
    POVDisplay(0b00000010);
    _delay_ms(150);
    
    POVDisplay(0b00000001);       // down to 0, restart
    _delay_ms(150);
    /*
    PORTD = 0;
    _delay_ms(10);                  // idk bro
    */
  }                                                    /* end mainloop */
  return 0;
}
