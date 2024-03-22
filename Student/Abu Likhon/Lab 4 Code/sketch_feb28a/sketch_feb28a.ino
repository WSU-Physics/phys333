#include <avr/io.h>
#include <util/delay.h>

void LEDTurnSignal(){
    // Initialize Data Direction Register B to output
    DDRD |= 0b00001111;
while(1){
    // Turn signal loop
   if (!(PINB & (1 << PB3))) {
   PORTD = 0b00000000;
   }else{

    for(int j = 0; j < 2; j++) { // Repeat the pattern to make it noticeable
        // Light up LEDs one by one
        for(int i = 0; i < 4; i++) {
            PORTD = (1 << i); 
            _delay_ms(250); // Adjust timing as needed
        }

        // Turn off LEDs in reverse order
        for(int i = 2; i >= 0; i--) {
            PORTD = (1 << i);
            _delay_ms(250); // Adjust timing as needed
        }
    }
   }

}
return 0;
}

int main(void) {
  // -------- Inits --------- //
  DDRD |= 0b11111111; // Set PORTD pins as output for LEDs
  DDRB &= ~(1 << PB3); // Set PB3 (Digital Pin 11) as input for the button
  PORTB |= (1 << PB3); // Enable pull-up resistor on PB3

  int state = 0; // Track the state of the LEDs

  // ------ Event loop ------ //
  while (1) {
    // Check if button is pressed (logic low when pressed because of pull-up resistor)
    if (!(PINB & (1 << PB3))) {
      _delay_ms(10); // Debounce delay
      while (!(PINB & (1 << PB3))); // Wait for button release
      _delay_ms(10); // Additional debounce delay

      state++; // Move to the next state
      if (state > 2) { // If state exceeds 2, reset to 0
        state = 0;
      }

      // Move the switch-case inside the button press logic
      switch (state) {
        case 0:
          PORTD = 0b00000000; // All LED Off
          break;
        case 1:
          LEDTurnSignal(); // Call the modified LED function for turn signal effect
          break;
        case 2:
          PORTD = 0b11110000; // First 4 LEDs on
          break;
      }
    }
    // Adding _delay_ms here might cause responsiveness issues with the button press.
    // _delay_ms(100); // Consider removing or adjusting this delay.
  }
  return 0;
}
