// ------- Preamble -------- //
#include <avr/io.h>            // Defines pins, ports, etc 
#include <util/delay.h>        // Functions to waste time
 
#define DELAY_MS 250           // Delay time in milliseconds
 
int main(void) {
 
  // -------- Inits --------- //
  DDRD |= 0b11111111;  // Data Direction Register D: writing a one to the bit enables output.
 
  // ------ Event loop ------ //
  while (1) {
    // Right turn signal
    for (int i = 4; i < 8; i++) {
        PORTD = (1 << i);      // Shift LED to the right
        _delay_ms(DELAY_MS);   // Delay
    }
    _delay_ms(DELAY_MS * 2);  // Extra delay between directions
    // Left turn signal
    for (int i = 3; i >= 0; i--) {
        PORTD = (1 << i);      // Shift LED to the left
        _delay_ms(DELAY_MS);   // Delay
    }
    _delay_ms(DELAY_MS * 2);  // Extra delay between directions
  }
 
  return 0;  // This line is never reached
}