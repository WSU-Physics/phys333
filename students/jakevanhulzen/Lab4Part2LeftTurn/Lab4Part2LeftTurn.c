// ------- Preamble -------- //
#include <avr/io.h>            
#include <util/delay.h>        
 
#define DELAY_MS 250           // Delay time in milliseconds
 
// Function to shift LEDs to the left
void shiftLeft() {
    for (int i = 3; i >= 0; i--) {
        PORTD = (1 << i);      // Shift LED to the left
        _delay_ms(DELAY_MS);   // Delay
    }
}
 
int main(void) {
 
  // -------- Inits --------- //
  DDRD |= 0b11111111;  // Data Direction Register
 
  // ------ Event loop ------ //
  while (1) {
    // Left turn signal
    shiftLeft();
  }
 
  return 0;  // This line is never reached
}