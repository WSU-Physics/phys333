#include <avr/io.h>
#include <util/delay.h>

void initIO(){
    // Set all PORTD pins as output
    DDRD = 0b11111111; 
    // Set PB3 and PB2 as inputs for the buttons
    DDRB &= ~((1 << PB3) | (1 << PB2)); 
    // Enable pull-up resistors on PB3 and PB2
    PORTB |= (1 << PB3) | (1 << PB2);
}

void LEDredTurnSignal(){
   
    // Use the first 4 LEDs for the red turn signal
    for(int j = 0; j < 2; j++) { // Repeat the pattern to make it noticeable
        for(int i = 0; i < 4; i++) {
            PORTD = (1 << i);
            _delay_ms(250); // Adjust timing as needed
        }
        for(int i = 2; i >= 0; i--) {
            PORTD = (1 << i);
            _delay_ms(250); // Adjust timing as needed
        }
    }
    // Ensure all LEDs are off before exiting
    PORTD = 0b00000000;
}
   


void LEDgreenTurnSignal(){


    // Use the last 4 LEDs for the green turn signal
    for(int j = 0; j < 2; j++) { // Repeat the pattern to make it noticeable
        for(int i = 4; i < 8; i++) {
            PORTD = (1 << i);
            _delay_ms(250); // Adjust timing as needed
        }
        for(int i = 6; i >= 4; i--) {
            PORTD = (1 << i);
            _delay_ms(250); // Adjust timing as needed
        }
    }
    // Ensure all LEDs are off before exiting
    PORTD = 0b00000000;

  
  return 0;
}

int main(void) {
    initIO(); // Initialize inputs and outputs

    // Event loop
    while (1) {
        // Check if the red button (PB3) is pressed
        if (!(PINB & (1 << PB3))) {
            _delay_ms(10); // Debounce delay
            while (!(PINB & (1 << PB3))); // Wait for button release
            _delay_ms(10); // Additional debounce delay
            LEDredTurnSignal(); // Activate red turn signal
        }
        
        // Check if the green button (PB2) is pressed
        if (!(PINB & (1 << PB2))) {
            _delay_ms(10); // Debounce delay
            while (!(PINB & (1 << PB2))); // Wait for button release
            _delay_ms(10); // Additional debounce delay
            LEDgreenTurnSignal(); // Activate green turn signal
        }
    }
    return 0;
}
