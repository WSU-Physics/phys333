// ------- Preamble -------- //
#include <avr/io.h>            // Defines pins, ports, etc 
#include <util/delay.h>        // Functions to waste time
 
#define DELAY_MS 250           // Delay time in milliseconds
 
void shiftLEDs(int start, int end, int direction) {
    for (int i = start; direction == 1 ? i < end : i >= end; i += direction) {
        PORTD = (1 << i);      // Shift LED
        _delay_ms(DELAY_MS);   // Delay
    }
}
 
int main(void) {
 
  // -------- Inits --------- //
  DDRD |= 0b11111111;  // Data Direction Register D: writing a one to the bit enables output.
 
  // ------ Event loop ------ //
  while (1) {
    // Right turn signal
    shiftLEDs(4, 8, 1); // Shift LEDs from 4 to 8 in the right direction
    _delay_ms(DELAY_MS * 2);  // Extra delay between directions
    // Left turn signal
    shiftLEDs(3, 0, -1); // Shift LEDs from 3 to 0 in the left direction
    _delay_ms(DELAY_MS * 2);  // Extra delay between directions
  }
 
  return 0;  // This line is never reached
}