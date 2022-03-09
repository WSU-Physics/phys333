//Source AVR:Make Programming Eliot Williams 

// POV toy demo framework //
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
 DDRD = 0xff; /* Set up all of LED pins for output */
 // ------ Event loop ------ //
 while (1) { /* mainloop */
 POVDisplay(0b00001110);
 POVDisplay(0b00011000);
 POVDisplay(0b10111101);
 _delay_ms(1000);
 POVDisplay(0b01110110);
 POVDisplay(0b00111100);
 POVDisplay(0b00111100);
 POVDisplay(0b00111100);
 POVDisplay(0b01110110);
 _delay_ms(1000);
 POVDisplay(0b10111101);
 POVDisplay(0b00011000);
 POVDisplay(0b00001110);
 PORTD = 0;
 _delay_ms(1000);
 } /* end mainloop */
 return (0);
}
