// ------- Preamble -------- //
#include <avr/io.h>            // Defines pins, ports, etc 
#include <util/delay.h>        // Functions to waste time
 
#define DELAY_MS 250           // Delay time in milliseconds
 
// Function to shift LEDs to the right
void shiftRight() {
    for (int i = 4; i < 8; i++) {
        PORTD = (1 << i);      // Shift LED to the right
        _delay_ms(DELAY_MS);  
    }
}
 
int main(void) {
 
  // -------- Inits --------- //
  DDRD |= 0b11111111;  // Data Direction Register D
 
  // ------ Event loop ------ //
  while (1) {
    // Right turn signal
    shiftRight();
  }
 
  return 0;  // This line is never reached
}