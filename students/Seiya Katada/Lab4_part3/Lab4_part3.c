// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON1_PIN PB0     //Pin for Button
#define LED1_PIN    PB1      //Pin for turn on LED
#define BUTTON2_PIN PB2     //Pin for Button
#define LED2_PIN    PB3      //Pin for turn on LED
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
    uint8_t button1State = 0; /* state */
    uint8_t button2State = 0; /* state */

    // -------- Inits --------- //
    DDRB &= ~(1 << BUTTON1_PIN);   // to set buttun as input. make button bit as 0
    PORTB |=  (1 << BUTTON1_PIN);  // To turn only BUTTON_PIN as 1

    DDRB &= ~(1 << BUTTON2_PIN);   // to set buttun as input. make button bit as 0
    PORTB |=  (1 << BUTTON2_PIN);  // To turn only BUTTON_PIN as 1

    // --- LED output ---
    DDRB |=  (1 << LED1_PIN);      //to set LED pin, PB1 as output
    PORTB &= ~(1 << LED1_PIN);     // LED OFF. put low

    DDRB |=  (1 << LED2_PIN);      //to set LED pin, PB1 as output
    PORTB &= ~(1 << LED2_PIN);     // LED OFF. put low

    while (1) {
        if (debounce(BUTTON1_PIN)) {
            if (button1State == 0) {
                PORTB ^= (1 << LED1_PIN);  
                button1State = 1;

                

            }     /* End event loop */
        } else {
            button1State = 0;   /* update the state */
        }
        if (debounce(BUTTON2_PIN)) {
            if (button2State == 0) {
                PORTB ^= (1 << LED2_PIN);  
                button2State = 1;
            }     /* End event loop */
        } else {
            button2State = 0;   /* update the state */
        }

    }
    return 0;
}
