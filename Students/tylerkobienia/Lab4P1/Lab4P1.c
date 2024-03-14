
 
#include <avr/io.h>
#include <util/delay.h>
 
#define DEBOUNCE_TIME 1000 // microseconds
 
uint8_t debouncePress(void) {
    if (bit_is_clear(PINB, PB0)) { // button is pressed now
        _delay_ms(DEBOUNCE_TIME);
        if (bit_is_clear(PINB, PB0)) { // still pressed
            return (1);
        }
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
    } 
    return 0; 
}