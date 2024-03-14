#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRB
#define LED_PORT PORTB
#define RIGHT_BUTTON_PIN PINC
#define LEFT_BUTTON_PIN PINC
#define RIGHT_BUTTON_BIT PINC0
#define LEFT_BUTTON_BIT PINC1

#define RIGHT_TURN 0
#define LEFT_TURN 1


void init_leds() {
    LED_DDR = 0xFF; // set all PORTB pins as output
}

void right_turn_animation() {
    for (int i = 0; i < 4; i++) {  // 4 steps for right turn animation
        LED_PORT = (1 << i);        // turn on LED sequentially from PB0 to PB3
        _delay_ms(200);             // delay for effect
           }
    _delay_ms(200);                 
}

// Function for left turn animation
void left_turn_animation() {
    for (int i = 3; i >= 0; i--) { // 4 steps for left turn animation
        LED_PORT = (1 << i);        // turn on LED sequentially from PB3 to PB0
        _delay_ms(200);             // delay for effect
    }
    _delay_ms(200);                 
}


int right_button_pressed() {
    if (!(RIGHT_BUTTON_PIN & (1 << RIGHT_BUTTON_BIT))) { // button is active low
        _delay_ms(10);  // debouncing delay
        if (!(RIGHT_BUTTON_PIN & (1 << RIGHT_BUTTON_BIT))) {
            return 1;   //pressed
        }
    }
    return 0;   //not pressed
}

int left_button_pressed() {
    if (!(LEFT_BUTTON_PIN & (1 << LEFT_BUTTON_BIT))) { // button is active low
        _delay_ms(10);  // debouncing delay
        if (!(LEFT_BUTTON_PIN & (1 << LEFT_BUTTON_BIT))) {
            return 1;   //pressed
        }
    }
    return 0;   // not pressed
}

int main() {
    init_leds();

    int right_turn_on = 0; // flag to track if right animation is on
    int left_turn_on = 0;  // flag to track if left animation is on

    while (1) {
        if (right_button_pressed()) { // check if right button is pressed
            if (!right_turn_on) {     // if right animation is not already on
                right_turn_animation(); // start right turn animation
                right_turn_on = 1;     // set flag to indicate animation is on
            } else {                  // if right animation is already on
                LED_PORT = 0x00;      // turn off LEDs
                right_turn_on = 0;    // reset flag to indicate animation is off
            }
            _delay_ms(200); 
        }

        if (left_button_pressed()) { // check if left button is pressed
            if (!left_turn_on) {     // if left animation is not already on
                left_turn_animation(); // start left turn animation
                left_turn_on = 1;     // set flag to indicate animation is on
            } else {                 // if left animation is already on
                LED_PORT = 0x00;     // turn off LEDs
                left_turn_on = 0;    // reset flag to indicate animation is off
            }
            _delay_ms(200); 
        }
    }

    return 0;
}
