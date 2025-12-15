#include <avr/io.h>
#include <util/delay.h>

void initIO() {
    DDRD = 0xFF; // Set all PORTD pins as output.
    DDRB &= ~((1 << PB3) | (1 << PB1)); // Set PB3 and PB1 as inputs.
    //  external pull-down resistors.
}

// It now returns true if a press is detected and false otherwise.
uint8_t debounceButton(uint8_t pin) {
    if (PINB & (1 << pin)) {
        _delay_ms(10); // Debounce delay
        if (PINB & (1 << pin)) {
            while(PINB & (1 << pin)); // Wait for button release
            return 1; // Button was pressed
        }
    }
    return 0; // Button was not pressed
}

// Function to run LED sequence and check for button press to exit.
void LEDSequence(uint8_t startPin, uint8_t buttonPin) {
    while(1) {
        for(uint8_t i = 0; i <= 4; i++) {
            if(debounceButton(buttonPin)) { // Check if button is pressed to exit
                PORTD = 0x00; // Turn off all LEDs before exiting
                return; // Exit the sequence if button is pressed again
            }
            PORTD = (0x0F >> (4 - i)) << startPin; // Set the LED pattern
            _delay_ms(100); // Delay between pattern changes
        }
    }
}

int main(void) {
    initIO(); // Initialize inputs and outputs
    
    while (1) {
        // Check if the red button (PB3) is pressed to start/stop red LED sequence
        if (debounceButton(PB3)) {
            LEDSequence(0, PB3); // Start red LED sequence with ability to stop it
        }
        
        // Check if the green button (PB1) is pressed to start/stop green LED sequence
        if (debounceButton(PB1)) {
            LEDSequence(4, PB1); // Start green LED sequence with ability to stop it
        }
    }

    return 0;
}
