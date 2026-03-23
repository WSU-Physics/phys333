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

        PORTD = 0b00001000;   // Turn on LEDs from left to right
        _delay_ms(100);

        PORTD = 0b00001100;
        _delay_ms(100);

        PORTD = 0b00001110;
        _delay_ms(100);

        PORTD = 0b00001111;
        _delay_ms(100);

    }

    return 0;
}
