                                                       /* Blinker Demo */

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */


int main(void) {
    // Initialize Data Direction Register B to output
    DDRD |= 0b11111111;

    // Event loop
    while (1) {
        // Running light effect
        for(int i = 0; i < 8; i++) {
            // Shift a '1' to the left to light up the next LED
            PORTD = (1 << i); 

            // Wait for some time
            _delay_ms(1000);

            // Optionally, turn off all LEDs before moving to the next one
            // PORTd = 0b00000000;
            // _delay_ms(100);
        }
    }

    // This line is never reached
    return 0;
}
