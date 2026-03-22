// ------- Preamble -------- //
#include <avr/io.h>        // Defines pins, ports, etc.
#include <util/delay.h>    // Delay functions

int main(void) {

    // -------- Inits --------- //
    DDRD = 0xFF;            // Set all PORTD pins as outputs

    // ------ Event loop ------ //
    while (1) {

        PORTD = 0b00000000;   // All LEDs off
        _delay_ms(100);

        PORTD = 0b00010000;   // Turn on LEDs from left to right
        _delay_ms(100);

        PORTD = 0b00110000;
        _delay_ms(100);

        PORTD = 0b01110000;
        _delay_ms(100);

        PORTD = 0b11110000;
        _delay_ms(100);

        // Add your right‑to‑left sequence here if needed
    }

    return 0;
}