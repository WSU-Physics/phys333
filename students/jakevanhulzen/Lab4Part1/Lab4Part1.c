#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_COUNT 5 // Number of samples for debouncing
#define DEBOUNCE_DELAY 10 // Delay between samples in milliseconds

uint8_t debouncePress(void) {
    uint8_t i, buttonState = 0;

    for (i = 0; i < DEBOUNCE_COUNT; i++) {
        if (bit_is_clear(PINB, PB0)) {
            buttonState++;
        }
        _delay_ms(DEBOUNCE_DELAY);
    }

    if (buttonState == DEBOUNCE_COUNT) {
        return 1; // Button is considered pressed
    }
    return 0;
}

int main(void) {
    // Inits
    uint8_t buttonWasPressed = 0; // state
    PORTB |= (1 << PB0); // enable the pull-up on the button
    DDRD = (1 << DDD0); // set up LED for output

    // Event loop
    while (1) {
        if (debouncePress()) {
            if (buttonWasPressed == 0) { // button wasn't last time through
                PORTD ^= (1 << PD0); // toggle LED
                buttonWasPressed = 1; // update the state
            }
        } else { // button is not pressed now
            buttonWasPressed = 0; // update the state
        }
    } // End event loop
    return 0; // This line is never reached
}