#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_COUNT 5 // Number of samples for debouncing

// Function to debounce button press
uint8_t debouncePress(uint8_t pin) {
    uint8_t i, buttonState = 0;

    for (i = 0; i < DEBOUNCE_COUNT; i++) {
        if (bit_is_clear(PINB, pin)) {
            buttonState++;
        }
        _delay_ms(1); 
    }

    if (buttonState == DEBOUNCE_COUNT) {
        return 1; 
    }
    return 0;
}

int main(void) {
    // Inits
    uint8_t rightButtonState = 0;
    uint8_t leftButtonState = 0;
    uint8_t rightAnimationRunning = 0;
    uint8_t leftAnimationRunning = 0;

    DDRD = 0xFF; 
    PORTB |= ((1 << PB0) | (1 << PB1)); 

    // Event loop
    while (1) {
        // Check for right turn signal button press
        if (debouncePress(PB1)) {
            if (!rightButtonState) { // Button was not pressed previously
                rightButtonState = 1; // Set button state
                rightAnimationRunning = !rightAnimationRunning; 
                leftAnimationRunning = 0; // Turn off left animation if running
                if (!rightAnimationRunning) {
                    PORTD &= 0xF0; // Turn off LEDs when animation stops
                }
            } else if (rightAnimationRunning) { // 
                rightAnimationRunning = 0; // Turn off animation
                PORTD &= 0xF0; // Turn off all LEDs
                rightButtonState = 0; // Reset button state
            }
        } else {
            rightButtonState = 0; // Reset button state
        }

        // Check for left turn signal button press
        if (debouncePress(PB0)) {
            if (!leftButtonState) { // Button was not pressed previously
                leftButtonState = 1; // Set button state
                leftAnimationRunning = !leftAnimationRunning; // 
                rightAnimationRunning = 0; // Turn off right animation if running
                if (!leftAnimationRunning) {
                    PORTD &= 0x0F; // Turn off LEDs when animation stops
                }
            } else if (leftAnimationRunning) { // 
                leftAnimationRunning = 0; // Turn off animation
                PORTD &= 0x0F; // Turn off all LEDs
                leftButtonState = 0; // Reset button state
            }
        } else {
            leftButtonState = 0; // Reset button state
        }

        // Run right turn signal animation
        if (rightAnimationRunning) {
            for (int i = 4; i < 8; i++) {
                PORTD = (1 << i); // Shift LED to the right
                _delay_ms(250); 
            }
        }

        // Run left turn signal animation
        if (leftAnimationRunning) {
            for (int i = 3; i >= 0; i--) {
                PORTD = (1 << i); // Shift LED to the left
                _delay_ms(250); 
            }
        }
    } // End event loop

    return 0; // This line is never reached
}