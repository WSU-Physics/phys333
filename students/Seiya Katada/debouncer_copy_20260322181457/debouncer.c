// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PB0    //Pin for Button
#define LED_PIN    PB1       //Pin for turn on LED
#define DEBOUNCE_US 1000     /* microseconds */

uint8_t debounce(void) {
    if (bit_is_clear(PINB, BUTTON_PIN)) {   
        _delay_us(DEBOUNCE_US);
        if (bit_is_clear(PINB, BUTTON_PIN)) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    uint8_t buttonState = 0; /* state */

    // -------- Inits --------- //
    DDRB &= ~(1 << BUTTON_PIN);   // to set buttun as input. make button bit as 0
    PORTB |=  (1 << BUTTON_PIN);  // To turn only BUTTON_PIN as 1

    // --- LED output ---
    DDRB |=  (1 << LED_PIN);      //to set LED pin, PB1 as output
    PORTB &= ~(1 << LED_PIN);     // LED OFF. put low

    while (1) {
        if (debounce()) {
            if (buttonState == 0) {
                PORTB ^= (1 << LED_PIN);  
                buttonState = 1;
            }     /* End event loop */
        } else {
            buttonState = 0;   /* update the state */
        }
    }
    return 0;
}

