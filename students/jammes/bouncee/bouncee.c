// POV toy demo framework - adapted by james g //

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// -------- Functions --------- //
void POVDisplay(uint8_t oneByte) { // i forgor what this does ( sets the output for leds to one byte? maybe )
  PORTD = oneByte;
  _delay_ms(2);
}

int main(void) {
  // -------- Inits --------- //
  DDRD = 0xff;                    // sets up leds as an output
  // ------ Event loop ------ //
  while (1) {                     // loop for pattern
    POVDisplay(0b10000001);       // starts with outside leds
    _delay_ms(50);
    
    _delay_ms(50);
    POVDisplay(0b01000010);       // moves in by one led on each side
    _delay_ms(50);
   
    _delay_ms(50);                
    POVDisplay(0b00100100);
    _delay_ms(50);
   
    _delay_ms(50);
    POVDisplay(0b00011000);        // hits the middle, goes back out
    _delay_ms(50);
  
    _delay_ms(50);
    POVDisplay(0b00100100);
    _delay_ms(50);

    _delay_ms(50);
    POVDisplay(0b01000010);
    _delay_ms(50);

    _delay_ms(50);
    POVDisplay(0b10000001);
    _delay_ms(10);                // shorter delay for bounciness
    /*
    PORTD = 0;
    _delay_ms(10);                // idk what this was for
    */
  }                                                    /* end mainloop */
  return 0;
}
